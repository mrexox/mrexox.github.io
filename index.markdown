---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
title: "Hi, dude 👋"
---

Nice to see you on my personal blog page. This blog is supposed to be about technical shit. There are probably not so many blogposts but they are increasing in number from time to time. There is a list of posts grouped by cetegory and also a chronological list of posts downside.

Feel free to notify me about inconvenience and mistakes (actually nobody does it, I know, but what if you do?).

## ⚙️ Writing Drivers
{% for post in site.categories.driver %}
 <li><span>{{ post.date | date_to_string }}</span> &nbsp; <a href="{{ post.url }}">{{ post.title }}</a></li>
{% endfor %}
