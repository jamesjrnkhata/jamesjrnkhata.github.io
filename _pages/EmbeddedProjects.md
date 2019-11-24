---
layout: archive
permalink: /embedded-projects/
title: "Embedded Project Posts"
author_profile: true
header:
  image: "/images/embedded_background.jpg"
---

<div class="tags-expo-section">

  {% for tag in site.categories %}

    {% if tag[0] == "embedded-projects" %}

      <ul class="tags-expo-posts">

        {% for post in tag[1] %}

          <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">

        <li>

          {{ post.title }}

        <small class="post-date">{{ post.date | date_to_string }}</small>

        </li>

        </a>

        {% endfor %}

      </ul>

    {% endif %}

  {% endfor %}

</div>
