#!/usr/bin/env python
# -*- coding: UTF-8 -*-
print 'Content-type: text/html\r\n\r'
print "<html>"
print "<h1>Hello World!</h1>"
print "</html>"

a = "hi"

print "hi"
print a

form = cgi.FieldStorage()
userID = form.getvalue("abc")
data = [] 