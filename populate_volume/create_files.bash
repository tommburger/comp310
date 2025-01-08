#!/bin/bash
#
#  Creates an assortment of files in the current directory
#  Used for checking out the filesystem information

# a zero length file
touch no_content

# a small file
echo "This is a very small file." > small_file

# a large file - one that requires more than 1 4k block
~/build_a_file large_file 5000

# a file that requires an indirect block with a block size of 4k
~/build_a_file has_indirect_blocks 58000

# files that test boundaries
~/build_a_file fourk 4096
~/build_a_file fourk_plus_1 4097

# a directory containing a variety of things
# file with a long name
# file with an 8.3 name
# deleted files
# hard links
# symbolic link

mkdir directory_1
cd directory_1
echo "sample file 1.1" > sample1.txt
echo "about to be deleted" > obsolete_file
echo "sample file 1.2" > sample2.txt
echo "also deleted file" > also_del
echo "file with a long name" > this_file_has_a_somewhat_long_name
rm obsolete_file
rm also_del
echo "this file has a 8.3 filename" > EIGHT3.TXT
ln -T sample1.txt lnk1.txt
ln -sT sample2.txt slnk2.txt
cd ..

# create a directory with a bunch of files
# this is to ensure that the second block group will be used
mkdir directory_2
cd directory_2

for i in {1..100}
do
    echo "this is file $i " > file_$i
done
echo "this is the last file" > last.txt

cd ..

echo "file creation complete"
