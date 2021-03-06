#!/usr/bin/python
# coding=utf-8
import datetime
import re
import sys
str1 = 'sprdfgu: d cap'; # for readline
str2 = '\d{2}-\d{2} \d{2}:\d{2}:\d{2}'; # for time
str3 = '\d*mAh'; # for mah

#store data in list
result = [];
list_time = []; 
list_value = [];
j = 0;
try:
	file_name = sys.argv[1]
	file= open(file_name, "rt", encoding="UTF-8",errors ='ignore')
	while True:
		content = file.readline();
		if not content:
			break;
		index_content = content.find(str1);
		if index_content!=-1:
			index_time = re.findall(str2, content);
			index_value = re.findall(str3, content);
			if index_time:
				list_time.append(''.join(index_time));
			if index_value:
				list_value.append((''.join(index_value))[0:-3]);
	file.close()

	while j < len(list_time):
		if j != (len ( list_time ) - 1):
			start_time = datetime.datetime.strptime ( list_time[j], '%m-%d %H:%M:%S' ) ;
			next_time = datetime.datetime.strptime ( list_time[j + 1], '%m-%d %H:%M:%S' ) ;
			time_space = (next_time - start_time).total_seconds () ;  # change to secound
			value_space = abs ( int ( list_value[j + 1] ) - int ( list_value[j] ) ) * 3600 ;
			current = value_space/time_space;
			print(start_time.strftime('%m-%d %H:%M:%S')+'---'+next_time.strftime('%m-%d %H:%M:%S')+"  current : %d"%current)
		j = j+1
except:
	print("please input file name")

