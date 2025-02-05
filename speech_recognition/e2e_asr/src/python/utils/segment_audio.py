#!/usr/bin/env python3
# -*- coding: utf-8 -*-

__author__ = 'Zhichali Li'
__email__ = '1072526820@com'
__copyright__ = 'Copyright 2021'

import argparse
import logging
import json
import os
import multiprocessing
from multiprocessing import Pool
import csv
from tqdm import tqdm
from pydub import AudioSegment

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



    def Run(self):
        logging.info("start to segment audio: {} with {}".format(audio_path, len(self.splits)))
        for i in tqdm(range(1, len(self.splits))):
            start = self.splits[i-1]
            end = self.splits[i]
            split = self.audio[start:end]
            name = os.path.join(save_prefix, str(i) + ".wav")
            split.export(name, format="wav")

def ArgsParser():
    parser = argparse.ArgumentParser("statistics dataset token info")
    parser.add_argument('--audio_path', required=True, type=str, action='store',
                        dest='audio_path', help="audio file path")
    parser.add_argument('--segments', required=True, type=str, action='store',
                        dest='segments', help="segments file path")
    parser.add_argument('--tg_path', required=True, type=str, action='store',
                        dest='tg_path', help="textgrid format transcription")
    args = parser.parse_args()
    return args

def main():
    args = ArgsParser()
    splits = []
    audio_path = args.audio_path
    with open(args.segments, 'r') as f:
        for line in f:
            _, index, start, end = line.strip().split()
            start = int(start)
            end = int(end)
            if start not in splits:
                splits.append(start)
            if end not in splits:
                splits.append(end)
    sg_audio = SegmentAudio(splits, audio_path, save_prefix=args.tg_path)
    sg_audio.Run()

if __name__ == "__main__":
    main()
