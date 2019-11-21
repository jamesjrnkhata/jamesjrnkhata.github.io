---
layout: archive
permalink: /software-projects/
title: "Software Project Posts"
author_profile: true
header:
  image: "/images/software_background.jpg"
---
{% for post in site.posts %}
  {% if site.categories == "Software-projects"  %}
    {% include archive-single.html %}
  {% endif %}  
{% endfor %}
