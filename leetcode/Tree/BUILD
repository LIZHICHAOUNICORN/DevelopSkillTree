package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "validate_binary_search_tree",
    srcs = [
        "validate_binary_search_tree.cc",
        "tree_node.h"
    ],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
