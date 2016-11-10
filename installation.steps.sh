sudo apt-get install gcc g++ python python-dev
sudo apt-get install qt4-dev-tools libqt4-dev
sudo apt-get install bzr
sudo apt-get install cmake libc6-dev libc6-dev-i386 g++-multilib
sudo apt-get install flex bison libfl-dev
sudo apt-get install libxml2 libxml2-dev
sudo apt-get install cvs
sudo apt-get install p7zip-full
sudo apt-get install python-pygoocanvas
sudo apt-get install python-pygraphviz

sudo apt install mercurial

wget http://www.nsnam.org/release/ns-allinone-3.26.tar.bz2
tar xjf ns-allinone-3.26.tar.bz2

./build.py

# Copy one of the examples
cp examples/tutorial/first.py scratch/

# Try running it
./waf --pyrun scratch/first

# Output should be something like:
# At time 2s client sent 1024 bytes to 10.1.1.2 port 9
# At time 2.00369s server received 1024 bytes from 10.1.1.1 port 49153
# At time 2.00369s server sent 1024 bytes to 10.1.1.1 port 49153
# At time 2.00737s client received 1024 bytes from 10.1.1.2 port 9

# Done Elhamdulillah, wait for the repo :D
