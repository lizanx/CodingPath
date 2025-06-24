FROM busybox
LABEL Maintainer="Gavin"
WORKDIR /testdir
RUN touch testfile1
COPY testfile2 ./
ADD compressed_file2.tar.gz ./decompressed/
ENV WELCOME="You're in my customized container, welcome!"
