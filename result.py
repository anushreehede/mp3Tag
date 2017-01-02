def results(results, num):
	#print "hello"
	for score, rid, title, artist in results:
		if num == "0":
			#print 0
			return score  
		if num == "1":
			#print 1
			return rid
		if num == "2":
			return title
		if num == "3":
			return artist
