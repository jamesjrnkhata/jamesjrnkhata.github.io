---
layout: default
permalink: /software-projects/
title: "Software Projects"
author_profile: true
header:
  image: "/images/software_background.jpg"
---


<div class="tags-expo-section">

  {% for tag in site.categories %}

    {% if tag[0] == "software-projects" %}

    <div id="custom_container">
      <ul class="custom_post" >

        {% for post in tag[1] %}

          <div id="container_left">

            <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">
              <img class="post_feature_img" src="{{ post.feature_img }}" />
            </a>

          </div>

          <div id="container_right">
            <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">

            <li>

              {{ post.title }}

            <small class="post-date">({{ post.date | date_to_string }})</small>

            </li>

            </a>
            {{ post.excerpt }}

          </div>


        {% endfor %}

      </ul>

    </div>

    {% endif %}

  {% endfor %}

</div>
