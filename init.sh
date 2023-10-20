git submodule update --init

if [ ! -d build ]; then
    mkdir build
fi

pushd build/
cmake ..
popd
