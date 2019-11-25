---
layout: archive
permalink: /software-projects/
title: "Software Projects"
author_profile: true
header:
  image: "/images/software_background.jpg"
---

</br>

<div class="tags-expo-section">

  {% for tag in site.categories %}

    {% if tag[0] == "software-projects" %}

    <div class="custom_container">
      <ul class="custom_post" >

        {% for post in tag[1] %}

          <div class="container_left">

            <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">
              <img width="110" height="110" src="{{ post.feature_img }}" />
            </a>

          </div>

          <div class="container_right">
            <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">

            <li>

              {{ post.title }}

            <small class="post-date">({{ post.date | date_to_string }})</small>

            </li>

            </a>

            <p>{{ post.excerpt }}</p>

          </div>


        {% endfor %}

      </ul>
    </div>

    {% endif %}

  {% endfor %}

</div>
