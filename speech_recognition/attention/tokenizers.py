#!/usr/bin/env/python3
""" 
Library implementing tokenizer.

Authors
* Zhichao Li 2022

"""
import os
import sentencepiece as spm
import logging

import edit_distance

FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)


class BaseTokenizer(object):
    """
    This class implements  base tokenizer.

    Arguments:
    ---------

    Example:
    --------
    >>>>
    """

    def encode(self, s):
        raise NotImplementedError

    def decode(self, inds, ignore_repeat=False):
        raise NotImplementedError

    def vocab_size(self):
        raise NotImplementedError

    def model_type(self):
        raise NotImplementedError

    def train(self):
        raise NotImplementedError

    def load_from_file(self, vocab_file):
        raise NotImplementedError

    def bos_idx(self):
        raise NotImplementedError

    def eos_idx(self):
        raise NotImplementedError

    def pad_idx(self):
        raise NotImplementedError

    def unk_idx(self):
        raise NotImplementedError

    def __repr__(self):
        return "type: {}, vocab: {}".format(self.model_type(),
                                            self.vocab_size())


class SubwordTokenizer(BaseTokenizer):
    """
    This class implements Subword tokenizer.

    Arguments:
    ---------

    Example:
    --------
    >>>>
    """

    def __init__(self,
                 model_dir,
                 vocab_size,
                 model_type,
                 max_sentence_piece_length,
                 charactor_coverage,
                 bos_id,
                 eos_id,
                 pad_id,
                 unk_id,
                 split_by_white_space,
                 add_dummy_prefix=True,
                 train=False,
                 text_file=None,
                 check_coverage=True):
        if model_type not in ["unigram", "bpe", "char"]:
            raise ValueError(
                "model_type must be one of : {unigram, bpe, char}, but now: {}".
                format(model_type))

        if not os.path.isdir(model_dir):
            logging.debug("{} not found, create it.".format(model_dir))
            os.makedirs(model_dir)

        if train and not os.path.isfile(text_file):
            raise ValueError("When train tokenizer, must have text_file")

        if not isinstance(vocab_size, int):
            raise ValueError(
                "vocab_size must be integer, but now: {}".format(vocab_size))

        self.prefix_model_file = os.path.join(
            model_dir,
            str(vocab_size) + "_" + model_type)

        self.vocab_size = vocab_size
        self.model_type = model_type
        self.charactor_coverage = charactor_coverage
        self.max_sentence_piece_length = max_sentence_piece_length

        self.bos_id = bos_id
        self.eos_id = eos_id
        self.pad_id = pad_id
        self.unk_id = unk_id

        self.split_by_whitespace = split_by_white_space
        self.model_file = self.prefix_model_file + ".model"
        self.add_dummy_prefix = str(add_dummy_prefix)

        if not os.path.isfile(self.model_file):
            logging.info("Train tokenizer with type: {}.".format(
                self.model_type))
            self.train()

        logging.info("==== Load Tokenizer ====")
        logging.info("Tokenizer path: {}.".foamt(self.model_file))
        logging.info("Tokenizer vocab_size: {}.".format(self.vocab_size))
        logging.info("Tokenizer model_type: {}.".format(self.model_type))
        self.sp = spm.SentencePieceProcessor()
        self.sp.load(self.model_file)

        if self.text_file and check_coverage:
            self.__check_coverage_from_bpe()

    def encode(self, s):
        return self.sp.encode_as_ids(s)

    def decode(self, idxs, ignore_repeat=False):
        crop_idx = []
        for t, idx in enumerate(idxs):
            if idx == self.eos_idx():
                break
            elif idx == self.pad_idx or (ignore_repeat and t > 0 and idx == idx[t-1]):
                continue
            else:
                crop_idx.append(idx)
        return self.sp.decode_ids(crop_idx)

    @property
    def vocab_size(self):
        return self.vocab_size

    @property
    def model_type(self):
        return self.model_type

    @classmethod
    def load_from_file(cls, vocab_file):
        sp = spm.SentencePieceProcessor()
        sp.load(vocab_file)
        return cls(sp)

    @property
    def bos_idx(self):
        return self.bos_id

    @property
    def eos_idx(self):
        return self.eos_id

    @property
    def pad_idx(self):
        return self.pad_id

    @property
    def unk_idx(self):
        return self.pad_id

    def train(self):
        """
        Train tokenizer with unsupervised techniques using SentencePieace Library.
        """
        query = ("--input=" + self.text_file 
                 + "  --model_type=" + self.model_type 
                 + "  --bos_id=" + self.bos_id 
                 + "  --eos_id=" + self.eos_id 
                 + "  --pad_id=" + self.pad_id 
                 + "  --unk_id=" + self.unk_id 
                 + "  --max_sentencepiece_length=" + self.max_sentencepiece_length 
                 + "  --character_coverage=" + self.character_coverage 
                 + "  --add_dummy_prefix=" + self.add_dummy_prefix
            )

        spm.SentencePieceTrainer.train(query)

    def __check_coverage_from_bpe(self):
        """
        Logging the accuracy of the bpe model to recover words from the training text.
        """
        wrong_recover_list = []
        with open(self.text_file, "r") as fin:
            for line in fin:
                row = line.split("\n")[0]
                encode_ids = self.sp.encode_as_ids(row)
                decode_text = self.sp.decode_ids(encode_ids)

                (details,) = edit_distance.wer_details_for_batch(
                        ["utt1"],
                        [row.split(" ")],
                        [decode_text.split(" ")],
                        compute_alignments=True,
                )
                if details["WER"] > 0:
                    for align in details["alignment"]:
                        if align[0] != "=" and align[1] is not None:
                            if align[1] not in wrong_recover_list:
                                wrong_recover_list.append(align[1])

        if len(wrong_recover_list) > 0:
            logging.info("Wrong recover words: {}.".format(len(wrong_recover_list)))
            logging.info("Tokenizer vocab_size: {}.".format(self.sp.vocab_size()))
            logging.info("Accuracy recovering words: {}".format(1 - float(len(wrong_recover_list)/self.sp.vocab_size())))

