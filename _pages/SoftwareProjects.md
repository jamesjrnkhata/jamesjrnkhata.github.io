---
layout: archive
permalink: /software-projects/
title: "Software Project Posts"
author_profile: true
header:
  image: "/images/software_background.jpg"
---

{% for category in site.categories %}
  <h3>{{category[0]}}</h3>
{% endfor %}
