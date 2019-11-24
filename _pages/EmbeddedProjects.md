---
layout: archive
permalink: /embedded-projects/
title: "Embedded Projects"
author_profile: true
header:
  image: "/images/embedded_background.jpg"
---

<div class="tags-expo-section">

  {% for tag in site.categories %}

    {% if tag[0] == "embedded-projects" %}

      <ul class="tags-expo-posts">

        {% for post in tag[1] %}

          <img src="{{ post.feature_img }}" />

          <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">

          <li>

            {{ post.title }}

          </li>

          </a>

          {{post.read_time}}.<small class="post-date">({{ post.date | date_to_string }})</small>

          <p>{{ post.excerpt }}</p>

        {% endfor %}

      </ul>

    {% endif %}

  {% endfor %}

</div>
