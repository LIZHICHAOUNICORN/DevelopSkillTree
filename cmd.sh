#!/bin/bash

# bazel clean --expunge
bazel build //leetcode/...
bazel build //codelab/...
