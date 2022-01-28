import argparse
import logging

FORMAT = '%(asctime)s %(filename)s %(funcName)s %(lineno)d %(message)s'
logging.basicConfig(level=logging.DEBUG, format=FORMAT)

# Global logging
logger = logging.getLogger(__name__)

_GLOBAL_ARGS = None

def _ensure_var_is_initialized(var, name):
    """Make sure the input variable is not None."""
    assert var is not None, '{} is not initialized.'.format(name)

def _ensure_var_is_not_initialized(var, name):
    """Make sure the input variable is not None."""
    assert var is None, '{} is already initialized.'.format(name)

def _add_demo_args(parser):
    group = parser.add_argument_group(title="pytorch distrubited Setup")
    group.add_argument('--size', required=False,
                        type=int, action='store',
                        default=2, dest='size')
    return parser

def parse_args(extra_args_provider=None, defaults={},
               ignore_unknown_args=False):
    parser = argparse.ArgumentParser(description="MachineLearningWorkflow Arguments",
                                     allow_abbrev=False)
    parser = _add_demo_args(parser)
    args = parser.parse_args()
    return args

def set_global_variables(extra_args_provider=None, defaults={},
                    ignore_unknown_args=False):
    """Parse entire arguments."""
    global _GLOBAL_ARGS
    _ensure_var_is_not_initialized(_GLOBAL_ARGS, 'args')
    _GLOBAL_ARGS = parse_args()
    return _GLOBAL_ARGS

def get_args():
    """Return arguments."""
    _ensure_var_is_initialized(_GLOBAL_ARGS, 'args')
    return _GLOBAL_ARGS
