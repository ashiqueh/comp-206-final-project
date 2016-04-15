#!/usr/bin/env python
# -*- coding: UTF-8 -*-

print 'Content-type: text/html\r\n\r'
print '<html>'
print '<body style="background-color:#333333; color:white">'
print '<center><img src="../logo-white-transparent.png"></center>'
print '<h1 style="text-align:center">Your new friends have been added!</h1>'

# stores usernames and fullnames of people retrived from usersWithFriends.txt
#user, pass, name, job

#get user ID from previous form submission
import cgi
form = cgi.FieldStorage()

userID = form.getvalue("userID") 

filename="friends.txt"
filename2="/home/2016/cvanei1/public_html/cgi-bin/users.txt"
friendsData=[] 
#stores list of usersWithFriends with friends
usersWithFriends=[]

# get all friendsData from usersWithFriends.txt
with open(filename, "rw") as f:
	friendsData = f.readlines()

#get list of usersWithFriends from friends.txt
for idx, item in enumerate(friendsData): 
	usersWithFriends.append(item.split()[0])

friends=[]
newFriends=[]

for idx in xrange(len(usersWithFriends)):
	friends.append([])

#friends[i] = list of friends of usersWithFriends[i]
for idx, item in enumerate(friends):
	friends[idx]=friendsData[idx].split()[1:]
	#print friends[idx]

data=[]
with open(filename2) as f:
	data = f.readlines()

#gets list of usernames of all registered users
usernames = data[0::4]

#removes current user's name from list
for idx, item in enumerate(usernames):
	if (usernames[idx].strip() == userID):
		usernames.pop(idx)

#now, usernames index numbers correspond to the checkbox index numbers from makefriends.py

test=""

for idx, item in enumerate(usernames):
	test=form.getvalue(str(idx))
	if (test=="on"):
		newFriends.append(usernames[idx])
	else:
		newFriends.append("")

#newFriends[i] stores whether or not usernames[i] was chosen as a new friend for uID

userFound = False

for i,item in enumerate(usersWithFriends):
	if (usersWithFriends[i].strip() == userID):
		userFound = True
		for j, item2 in enumerate(newFriends):
			if ((newFriends[j].strip() not in friends[i]) and (newFriends[j] != "")):
				friends[i].append(newFriends[j])

#for idx, item in enumerate(friends):
#	if (usersWithFriends[idx].strip() == userID):
#		print usersWithFriends[idx] + ": "
#		for j, jtem in enumerate(friends[idx]):
#			print friends[idx][j]

#clear the file with friends
#open(filename, 'w').close()
#open the file
friendsFile=open(filename, "w").close()
friendsFile=open(filename, "w")

#if user was found, write new file.
line=""

for idx,item in enumerate(usersWithFriends):
	for j,item2 in enumerate(friends[idx]):
		friends[idx][j]=friends[idx][j].strip()
	line += usersWithFriends[idx].strip()
	line += " "
	line += " ".join(friends[idx])
	line += "\n"
	friendsFile.write(line)
	line = ""

#if user wasn't found, write a new line with the user.
if not userFound:
	line += userID.strip()
	for j,item in enumerate(newFriends):
		line += " " 
		line += newFriends[j].strip()
	line += "\n"
	friendsFile.write(line)

friendsFile.close()


print '<center><form action="http://cgi.cs.mcgill.ca/~jzuo1/cgi-bin/dashboard.py" method="POST">'
print '<input type="hidden" name="userID" value="' + userID.strip('\n') + '">'
print '<input type="submit" value="Return to dashboard">'
print '</body>'
print '</html>'