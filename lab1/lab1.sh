# Name: Kavya Sharma
# Date: 25th Sept. 2024
# Title: Lab1
# Description: Unix/Linux Commands and Basic Shell Programming

echo Executing $0
echo $(/bin/ls | wc -l) files
wc -l $(/bin/ls)
echo "HOME="$HOME
echo "USER="$USER
echo "PATH="$PATH
echo "PWD="$PWD
echo "\$\$"=$$
user=`whoami`
numusers=`who | wc -l`
echo "Hi $user! there are $numusers logged on."
if [ $user = "krsharma" ]
then
echo "Now you can proceed!"
else
echo "Check who logged in!"
exit 1
fi

response="Yes"
while [ $response != "No" ]
do
echo "Enter height of rectangle: "
read height
echo "Enter width of rectangle: "
read width
area=`expr $height \* $width`
echo "The area of the rectangle is $area"

echo "Would you like to repeat for another rectangle [Yes/No]?"
read response
done

echo "Enter radius of circle: "
read r
rsq=$(($r*$r))
carea=`echo "3.14*$rsq" | bc`
echo "The area of the circle is $carea"
