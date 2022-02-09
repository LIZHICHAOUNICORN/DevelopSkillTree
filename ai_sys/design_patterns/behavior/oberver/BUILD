package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "num_gen_main",
    srcs = [
        "num_gen_main.cc",
	"digit_observer.h",
	"graph_observer.h",
	"num_gen.h",
	"random_num_gen.h",
	"num_gen_observe.h",
    ],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
