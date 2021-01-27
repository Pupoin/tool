a=`find . -type d | grep  "./"`

for dir in $a
do
	cp index.php $dir
done

echo "copy index.php successfully!"
