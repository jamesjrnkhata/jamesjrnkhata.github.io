---
layout: archive
permalink: /software-projects/
title: "Software Project Posts"
author_profile: true
header:
  image: "/images/software_background.jpg"
---
{% for category in site.categories %}
  {% if category[0] == "software-projects"  %}
    {% for post in posts %}
    {% include archive-single.html %}
    {% endfor %}
  {% else %}
    <h2>Out of category</h2>
    {% include archive-single.html %}
  {% endif %}  
{% endfor %}
