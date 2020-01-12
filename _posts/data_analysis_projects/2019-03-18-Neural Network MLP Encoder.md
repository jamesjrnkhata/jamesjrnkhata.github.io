---
title: "Neural Network Multi-Layer Perceptron (Encoder)"
date: 2019-03-18
categories: [data-analysis-projects]
permalink: /:categories/:title/
feature_img: /images/data_analysis_projects/neuralnetworkmlpencoder/neuralnetworkmlpencoder_img00.jpg
excerpt: "matlab, machine learnning, neural network, software, encoder, ebp"
purpose: "This assignment aimed at building an Error Back-Propagation training algorithm (EBP) for a multi-layer perceptron (MLP) 4-2-4 encoder using Python."
toc: true
classes: wide
images:
  - image_path: /images/data_analysis_project/neuralnetworkmlpencoder/neuralnetworkmlpencoder_img00.jpg
    title: "Figure 1 - MLP 4-2-4 Encoder Structure"
    weight: 1
---

<h2 class="text-underline">Purpose</h2>

This assignment aimed at building an Error Back-Propagation training algorithm (EBP) for a multi-layer perceptron (MLP) 4-2-4 encoder using Matlab.

The MLP had an input layer of four units, a hidden layer of two units and an output layer of four units. 	

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 1 %}
      <li>
        <figure class="custom-figure">
          <img src="{{ image.image_path }}" alt="{{ image.title }}">
          <figcaption class="custom-figcaption">
            {{ image.title }}
          </figcaption>
        </figure>  
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

The system was supposed to take a four-unit input pattern encode it using the hidden layer and output a four-unit output pattern as shown in the table below.

<span class="custom-tablecaption">Table 1: Input to Desired Output patterns for the 4-2-4 Encoder</span>

| Input Pattern | Desired Output Pattern |
| ------------- | :--------------------: |
| 1  0  0  0 | 1  0  0  0 |
| 0  1  0  0 | 0  1  0  0 |
| 0  0  1  0 | 0  0  1  0 |
| 0  0  0  1 | 0  0  0  1 |

<h2 class="text-underline">Procedure</h2>

<h2 class="text-underline">Implementation</h2>

### Software

<h2 class="text-underline">Conclusion</h2>
