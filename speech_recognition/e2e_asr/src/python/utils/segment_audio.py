#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Zhichali Li'
__email__ = 'zhichaoli@mobvoi.com'
__copyright__ = 'Copyright 2021, Mobvoi Inc.'

import argparse
import logging
import json
import os
import multiprocessing
from multiprocessing import Pool
import csv
from tqdm import tqdm
from pydub import AudioSegment
import textgrid

FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.INFO, format=FORMAT)

class SegmentAudio(object):
    """
    splits: split list.
    audio_path: the audio file path.
    """
    def __init__(self, splits, audio_path, save_prefix=None, save_fmt="wav"):
        self.audio = AudioSegment.from_wav(audio_path)
        self.splits = splits
        if save_prefix is None:
            save_prefix = os.getcwd()

    def Run():
        logging.info("start to segment audio: {} with {}".format(audio_path, len(self.splits)))
        for i in tqdm(range(1, len(self.splits))):
            start = self.splits[i-1]
            end = self.splits[i]
            split = self.audio[start:end]
            name = os.path.join(save_prefix, str(i) + ".wav")
            split.export(name, format="wav")

def ParseTextGridFmtText(tg_path, audio_prefix):
    logging.info("Parse textgrid file: {}".format(tg_path))
    splits = [0]
    seq_name = []
    tg = textgrid.TextGrid.fromFile(tg_path)
    names = []
    duration = tg.maxTime
    audio_name = tg[0].name
    f_id, path_session, _ = audio_name.split('-')
    # Parse audio path
    audio_path = "/ssd/nfs08/huiding/raw-data/conversion3k/wav/Conversation{}/{}/{}".format(f_id, path_session, audio_name)
    last_name = None
    for i in tqdm(range(len(tg[0]))):
        name = tg[0][i]
        if name is not None and name not in names:
            names.append(name)
        if name is not None and name != last_name:
            continue
        else:
            inter = tg[0][i].xmax
            splits.append(inter)
            seq_name.append(name)
            last_name = name
    logging.info("duration: {}, speaker: {}, "
                 "totle splits: {}, audio_path: {}".format(duration,
                                                           repr(names),
                                                           len(splits),
                                                           audio_path))
    return splits, seq_name

def ArgsParser():
    parser = argparse.ArgumentParser("statistics dataset token info")
    parser.add_argument('--audio_path', required=True, type=str, action='store',
                        dest='audio_path', help="audio file path")
    parser.add_argument('--tg_path', required=True, type=str, action='store',
                        dest='tg_path', help="textgrid format transcription")
    args = parser.parse_args()
    return args

def main():
    args = args_parser()
    splits = []
    audio_path = args.audio_path
    SegmentAudio sg_audio(splits, audio_path)
    sg_audio.Run()

if __name__ == "__main__":
    main()
