FROM gcc:11.3.0

WORKDIR /home/app

RUN apt-get update \
    && apt-get upgrade -y \
    && apt-get install ruby-full -y \
    && gem install bundler \
    && gem install ceedling