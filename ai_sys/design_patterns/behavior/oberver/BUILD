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
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
    linkopts = ['-lm', '-lpthread'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
