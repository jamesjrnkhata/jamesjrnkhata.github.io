---
layout: archive
permalink: /software-projects/
title: "Software Projects"
author_profile: true
header:
  image: "/images/software_background.jpg"
---

<div class="tags-expo-section">

  {% for tag in site.categories %}

    {% if tag[0] == "software-projects" %}

      <ul >

        {% for post in tag[1] %}

          <img src="{{ post.feature_img }}" />

          <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">

          <li>

            {{ post.title }}

          <small class="post-date">({{ post.date | date_to_string }})</small>

          </li>

          </a>

          <p>{{ post.excerpt }}</p>

        {% endfor %}

      </ul>

    {% endif %}

  {% endfor %}

</div>
