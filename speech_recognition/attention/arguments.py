""" Arguments for training.

Authors
 * Zhichao Li 2022
"""

import yaml
import argparse

def parse_arguments():
    parser = argparse.ArgumentParser(description='Training asr.')
    parser.add_argument('--config', type=str, required=True, help='Path to training config.')
    parser.add_argument('--test', action='store_true', help='Test the model.')
    args = parser.parse_args()
    return args

