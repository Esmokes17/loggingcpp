FROM ubuntu
COPY ./ ./app
RUN apt-get -y update
RUN apt-get install -y g++ libgtest-dev cmake
WORKDIR "./app"
RUN chmod 755 ./run_test.sh