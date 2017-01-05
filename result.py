def results(results, field):
	#print "hello"
	#first = True
	#print results
	for score, rid, title, artist in results:
		"""if first:
			first = False 
		else:
		    print() """  
		print field
		#print results[field]
		if field == 0:
		    score = score*100
		    newscore = str(score) 
		    print newscore
		    return newscore  
		if field == 1:
		    print rid
	        return rid
		if field == 2:
			print title
			print "two"
			return title
		if field == 3:
			print artist
			print "three"
			return artist


