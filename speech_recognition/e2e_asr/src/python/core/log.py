import logging
from logging import CRITICAL
from logging import DEBUG
from logging import ERROR
from logging import INFO
from logging import WARNING

import os
import sys
import threading

log_levels = {
    "debug": logging.DEBUG,
    "info": logging.INFO,
    "warning": logging.WARNING,
    "error": logging.ERROR,
    "critical": logging.CRITICAL,
}

_lock = threading.Lock()
_default_log_level = logging.DEBUG
_default_handler = None
_default_formatter = logging.Formatter('%(asctime)s-%(levelname)s-%(filename)s-%(lineno)d-%(message)s')

def _get_default_log_level():
    env_log_level = os.getenv("ASR_LOG_LEVEL")
    if env_log_level:
        if env_log_level in log_levels:
            return log_levels[env_log_level]
        else:
            logging.getLogger.warning(
                    f"Unknown option ASR_LOG_LEVEL={env_log_level}, "
                    f"has to be one of ', '.join(log_levels.keys())"
                    )
    return _default_log_level

def _get_library_name():
    return __name__.split('.')[0]


def _configure_library_root_logger():
    global _default_handler
    with _lock:
        if _default_handler:
            return
        _default_handler = logging.StreamHandler(stream=sys.stdout)
        _default_handler.setFormatter(_default_formatter)
        _default_handler.flush = sys.stdout.flush

        library_root_logger = logging.getLogger(_get_library_name())
        library_root_logger.addHandler(_default_handler)
        library_root_logger.setLevel(_get_default_log_level())
        # library_root_logger.propagate = False

def get_logger(name=None):
    if name is None:
        name = _get_library_name()
    _configure_library_root_logger()
    return logging.getLogger(name)
