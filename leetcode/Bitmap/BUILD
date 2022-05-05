package(default_visibility = ["//visibility:public"])
cc_binary(
    name = "implement_trie_prefix_tree",
    srcs = ["implement_trie_prefix_tree.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
