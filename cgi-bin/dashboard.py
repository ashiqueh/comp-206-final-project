#!/usr/bin/env python
# -*- coding: UTF-8 --

#Module imports
import os
import readline
import cgi

#Gets the current user from POST
form = cgi.FieldStorage()
userID = form.getvalue("userID")

#The start of the dashboard HTML up to the status post
print 'Content-type: text/html\r\n\r'
print '''
<html>
<div style="width:100%">

<head><title> Your EliteDragons Dashboard </title></head>

<body bgcolor="#333333" text="white">

<div>
<center>
        <img src="http://cs.mcgill.ca/~ahossa5/logo-white-transparent.png">
</center>
</div>

<div style="float:left; width:30%">
	Home
	<form action="http://cs.mcgill.ca/~ahossa5/welcome.html">
		<input type="submit" value="Logout">
	</form>

	<form action="http://cs.mcgill.ca/~ahossa5/cgi-bin/makefriends.py" method="POST">
		<input type="hidden" name="userID" value="'''+userID+'''">
		<input type="submit" value="Make a friend">
	</form>

	<form action="http://cgi.cs.mcgill.ca/~jzuo1/cgi-bin/seeFriends.cgi" method="POST">
		<input type="hidden" name="userID" value="'''+userID+'''">
		<input type="submit" value="See a friend">	
	</form>
</div>
	
<div style="float:right; width:70%">
	<center>
	Enter your status here:
	<form action="status.py" method="POST">
		<input type="hidden" name="userID" value="'''+userID+'''">
		<br>
		<input type="text" name="status">
		<br>
		<input type="submit" value="Post your status!">
	</form>
	</center>
	'''

#Returns a list of the user's friends
def getFriends(userID):
	#Opens the friends document and stores each line as a string in a list
	allFriends = [line for line in file("/home/2014/ahossa5/public_html/cgi-bin/friends.txt", "r")]
	#Scans the document until the current user is found or we reach the end
	for line in allFriends:
		#Tokenizes the list and checks the first token of the string, which will be the current user
		tokenizedLine = line.split(' ')
		for i, friend in enumerate(tokenizedLine):
			tokenizedLine[i] = tokenizedLine[i].strip()
		if tokenizedLine[0] == userID:
			#print "The user and his friends are " + line
			#Returns the line
			return tokenizedLine
	randomList = []
	randomList.append(userID)
	return randomList
	#return 0

#Generates the status updates of the user's friends
def genStatus(userID):
	#Gets the user's friends
	friends = getFriends(userID)
	#if friends[0] != userID:
	#	friends[0] = userID
	
	#New list to store the statuses of the friends
	result = '<center> What are your friends saying? <table border="0">'
	#Opens the status.txt document and stores each line as a string in a list
	allStatus = [line for line in file("../status.txt", "r")]
	
	#Initializes a counter to keep track of the number of statuses added
	numStatus = 0
	#allStatus is reversed because the last element is the most recent and needs to be appended to the result first
	for status in reversed(allStatus):
		#Stops the loop if 20 statuses have been added
		if numStatus >= 20:
			break
		#print "Looked at status: " + status
        #Splits the status into username and status and checks if the first token of the split, which is a username, matches one of the current user's friends
		tokenizedStatus = status.partition(' ')
		for friend in friends:
			#If the status belongs to a friend, it is added to the dashboard output
			if tokenizedStatus[0] == friend:
	            #Appends the status to the line
				status = "<tr> <td>" + tokenizedStatus[0] + ":</td> <td>" + tokenizedStatus[2] + "</td></tr>"
				result = result + status
				#Counter is incremented
				numStatus = numStatus + 1
				break

	return result + "</table></center>"

#Executes the function to populate the status list
print genStatus(userID)


#The end of the dashboard HTML
print '''
</div>
</div>
</body>
</html>
'''
