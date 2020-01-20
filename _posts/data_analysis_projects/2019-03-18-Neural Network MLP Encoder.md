---
title: "Neural Network Multi-Layer Perceptron (Encoder)"
date: 2019-03-18
categories: [data-analysis-projects]
permalink: /:categories/:title/
feature_img: /images/data_analysis_projects/neuralnetworkmlpencoder/neuralnetworkmlpencoder_img00.jpg
excerpt: "matlab, deep learning, neural network, software, encoder, ebp"
purpose: "This assignment aimed at building an Error Back-Propagation training algorithm (EBP) for a multi-layer perceptron (MLP) 4-2-4 encoder using Matlab."
toc: true
classes: wide
images:
  - image_path: /images/data_analysis_projects/neuralnetworkmlpencoder/neuralnetworkmlpencoder_img00.jpg
    title: "Figure 1 - MLP 4-2-4 Encoder Structure"
    weight: 1
  - image_path: /images/data_analysis_projects/neuralnetworkmlpencoder/neuralnetworkmlpencoder_img01.jpg
    title: "Figure 2 - How Weights affect Errors (Neural Network Tutorial 2014)"
    weight: 2
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

To train a Multi-layer perceptron encoder, Forward propagation was carried out were the input pattern was passed into the system through the input layer (layer I) nodes. The sum of the values from layer I were used as input for the hidden layer (layer J). The values of outputs from layer I were each multiplied with their corresponding Weights (W1) value before summing them up and then adding a set of Bias (Bias_J) values, before using them as input for the hidden layer (layer K) nodes. Using expression:

y = (W1’ * input) + Bias_J

These Weights and Bias were used to influence the system later when training it. The hidden layer then passed its values as Input to the Outer layer (layer K).

For the output layer (layer K), to use the values from the hidden layer, hidden layer values were passed through an activation function (sigmoid function). Using dot product expression for Element-wise calculation:

Out_J = 1./(1+exp(-y))

Sigmoid function was used to determine if the node’s output activates (fires) or not to influence its following node. The input values to layer K nodes were also multiplied with a different set of their corresponding Weights (W2) summed up and then added to another set of Bias (Bias_K).

Out_K = (W2' * Out_J) + Bias_K

The resulting values were the outputs for layer K and the system. These outputs were then compared to the Desired Output pattern (Target Output) and calculating the difference between the two to determine the Error.

Error = Actual Output – Target Output

Error Back-Propagation (EBP) was then used to make the adjustments to the Weights and Bias to reduce the Error in turn training the system to work as desired.

The influence of changes in the Weights (W1 and W2) were determined through partial derivation of the functions of the Forward propagation of the system.

<ul class="photo-gallery-col">
  {% for image in page.images %}
    {% if image.weight == 2 %}
      <li>
        <figure class="custom-figure">
          <img class="galley_img" src="{{ image.image_path }}" alt="{{ image.title }}">
          <figcaption class="custom-figcaption">
            {{ image.title }}
          </figcaption>
        </figure>  
      </li>
    {% endif %}  
  {% endfor %}  
</ul>

Small delta k (𝛿K) for each node of layer K was determined by the expression:

𝛿k = Ok * (1 – Ok) (Ok – tk)

were OK was the Actual Output and tk was the Target Output of that specific node. Changes for weights (W2) between layer J and K (Wjk) were then calculated by the expression:

𝛿E / 𝛿Wjk = Oj 𝛿k

were Oj was the output from the previous node (hidden layer). Small delta j (𝛿j) for each node of layer J was determined by the expression:

𝛿j = Oj * (1 – Oj) * ∑ 𝛿k Wjk

were Oj was the output from hidden layer (layer J) and ∑𝛿k Wjk was the sum of all layer K nodes connected to corresponding layer J node. Changes for weights (W1) between layer I and J (Wij) were then calculated by the expression:

𝛿E / 𝛿Wij = Oi 𝛿j

were Oi was the outputs from the input layer (layer I) nodes connected to that node of layer J. The weights (W1 and W2) were then updated (replaced) using expressions:

<span class="custom-tablecaption">Table 2: Expressions used to update the values of weights W1 and W2</span>

| Weights  | Weight Updating Expression |
| ------------- | :--------------------: |
| W2 (W<sub>jk</sub>) | Wjk = Wjk + (- learning rate * Oj 𝛿k) |
| W1 (Wij) | Wij = Wij + (- learning rate * Oi 𝛿J) |



<h2 class="text-underline">Implementation</h2>

### Software

<h2 class="text-underline">Conclusion</h2>
