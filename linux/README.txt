These shared libraries were compiled against an x86_64 architecture, there's no guarantee that
they will work for your Linux install, but in theory you should be able to copy them to /usr/lib64
run "ldconfig" as root, and then you should be set to compile and go.
