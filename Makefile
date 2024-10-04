all: index.html

clean:
	rm -f index.html

index.html: index.md templates/home-template.html Makefile
	pandoc --toc -s --css reset.css --css index.css -i $< -o $@ --template=templates/home-template.html

blog/%.html: blog/%.md templates/post-template.html Makefile
	pandoc --toc -s --css reset.css --css index.css -i $< -o $@ --template=templates/post-template.html

serve:
	python3 -m http.server

.PHONY: all clean serve
