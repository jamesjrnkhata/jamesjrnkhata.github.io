---
layout: archive
permalink: /software-projects/
title: "Software Project Posts"
author_profile: true
header:
  image: "/images/software_background.jpg"
---

{% for post in site.posts %}
  {% if post.categories[0] == "software-projects" %}
    <h1>{{ categories[0] }}</h1>
  {% endif %}  
{% endfor %}
