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


      <ul class="custom_post" >

        {% for post in tag[1] %}
        <div id="custom_container">
          <div id="container_left">
          {% if post.feature_img %}
            <div class="post_feature_img" style="background-image: url({{ post.feature_img }})">
            </div>
          {% else %}
            <div class="post_feature_img" style="background-image: url({{ page.blank_feature_img }})">
            </div>
          {% endif %}  


          </div>

          <div id="container_right">
            <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">

            <li>

              {{ post.title }}

            <small class="post-date">({{ post.date | date_to_string }})</small>

            </li>

            </a>
              <p class="page__meta-custom">{{ post.excerpt }}</p>

              <p class="archive__item-excerpt">{{ post.purpose | truncatewords: 25 }}
              <a class="post-title" href="{{ site.baseurl }}{{ post.url }}">
              Read more.
              </a> </p>

          </div>
        </div>

        {% endfor %}

      </ul>



    {% endif %}

  {% endfor %}

</div>
