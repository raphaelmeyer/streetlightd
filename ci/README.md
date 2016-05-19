Building and Continuous integration
===================================

The software is buildable within a docker container which itself can be built with the provided Dockerfile.
If you want to build the software on your machine, have a look in the Dockerfile.

To build and test the project and generate the documentation, execute the following steps in the root directory:

    docker build -t streetlightd ci/
    docker run -v `pwd`:/home/root/streetlightd streetlightd bash -c "cd home/root/streetlightd/; ci/build.sh"
    docker run -v `pwd`:/home/root/streetlightd streetlightd bash -c "cd home/root/streetlightd/; ci/test.sh"
    docker run -v `pwd`:/home/root/streetlightd streetlightd bash -c "cd home/root/streetlightd/; ci/documentation.sh"

