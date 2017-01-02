def results(results, num):
	print "hello"
	for score, rid, title, artist in results:
		if num == 0:
			score = score*100
			newscore = str(score)
			#newscore = "{:.2f}".format(score) 
			print newscore
			return newscore  
		if num == 1:
			print rid
			return rid
		if num == 2:
			print title
			return title
		if num == 3:
			#print artist
			return artist
