#!/usr/bin/env/python3
""" 
Library implementing edit distance.

Authors
* Zhichao Li 2022

"""
import logging
import collections


# TODO(zhichaoli) remove this to yaml
FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)

EDIT_SYMBOLS = {
        "eq": "=",
        "ins": "I",
        "del": "D",
        "sub": "S",
    }


def _batch_to_dict_format(ids, seqs):
    return dict(zip(ids, seqs))


def wer_detail_for_batch(ids, refs, hyps, compute_alignments=False):
    """
    compute wer for batch.

    """
    refs = _batch_to_dict_format(ids, refs)
    hyps = _batch_to_dict_format(ids, hyps)

    return wer_details_by_utterance(refs,
                                    hyps,
                                    compute_alignments=compute_alignments,
                                    scoring_mode="strict")


def wer_details_by_utterance(ref_dict,
                             hyp_dict,
                             compute_alignments=False,
                             scoring_mode="strict"):
    details_by_utterance = []
    for key, ref_tokens in ref_dict.items():
        utterance_details = {
            "key": key,
            "ref_tokens": ref_tokens if compute_alignments else None,
            "hyp_tokens": None,
            "WER": None,
        }

        if key in hyp_dict:
            hyp_tokens = hyp_dict[key]
        else:
            raise ValueError(
                "when compute edit distance, hyp_dict must have key: {}.".
                format(key))

        table = op_table(ref_tokens, hyp_tokens)
        ops = count_ops(table)

        utterance_details.update(
            {"WER": 100.0 * sum(ops.values()) / len(ref_tokens)})

        details_by_utterance.append(utterance_details)

    return details_by_utterance


def op_table(a, b):
    """
    Levenshtein distance

    """
    prev_row = [j for j in range(len(b) + 1)]
    cur_row = [0] * (len(b) + 1)

    table = [[EDIT_SYMBOLS["eq"]
              for j in range(len(b) + 1)]
             for i in range(len(a) + 1)]

    for i in range(len(a) + 1):
        table[i][0] = EDIT_SYMBOLS["del"]
    for j in range(len(b) + 1):
        table[0][j] = EDIT_SYMBOLS["ins"]

    table[0][0] = EDIT_SYMBOLS["eq"]
    for i, a_token in enumerate(a, start=1):
        cur_row[0] += 1
        for j, b_token in enumerate(b, start=1):
            insertion_cost = cur_row[j - 1] + 1
            deletion_cost = prev_row[j] + 1
            substitution = 0 if a_token == b_token else 1
            substitution_cost = prev_row[j - 1] + substitution

            # insertion > deletion > substitution
            if substitution_cost < insertion_cost and substitution_cost < deletion_cost:
                cur_row[j] = substitution_cost
                if substitution:
                    table[i][j] = EDIT_SYMBOLS["sub"]
            elif deletion_cost < insertion_cost:
                cur_row[j] = deletion_cost
                table[i][j] = EDIT_SYMBOLS["del"]
            else:
                cur_row[j] = insertion_cost
                table[i][j] = EDIT_SYMBOLS["ins"]
        prev_row[:] = cur_row[:]

    return table


def count_ops(table):
    edits = collections.Counter()
    i = len(table) - 1
    j = len(table[0]) - 1
    while not (i == 0 and j == 0):
        if i == 0:
            edits["insertions"] += 1
            j -= 1
        elif j == 0:
            edits["delations"] += 1
            i -= 1
        else:
            if table[i][j] == EDIT_SYMBOLS["ins"]:
                edits["insertions"] += 1
            elif table[i][j] == EDIT_SYMBOLS["del"]:
                edits["delations"] += 1
            else:
                if table[i][j] == EDIT_SYMBOLS["sub"]:
                    edits["substitutions"] += 1
                i -= 1
                j -= 1
    return edits
