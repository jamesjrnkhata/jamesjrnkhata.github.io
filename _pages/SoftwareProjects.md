---
layout: archive
permalink: /software-projects/
title: "Software Project Posts"
author_profile: true
header:
  image: "/images/software_background.jpg"
---

<div class="tags-expo-section">

  {% for tag in site.categories %}

    {% if tag[0] == "software-projects" %}

      <ul class="tags-expo-posts">

        {% for post in tag[1] %}

          <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">

        <li>

          {{ post.title }}

        <small class="post-date">({{ post.date | date_to_string }})</small>

        </li>

        </a>

        {% endfor %}

      </ul>

    {% endif %}

  {% endfor %}

</div>
