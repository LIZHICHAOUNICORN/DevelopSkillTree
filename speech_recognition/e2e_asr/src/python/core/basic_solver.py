import abc
import os
import sys

from utils.logging import get_logger

logger = get_logger(__name__)

class BaseSolver():
    '''
    Arguments:
        config: yaml-styled config
        paras: argparse parameters
    '''
