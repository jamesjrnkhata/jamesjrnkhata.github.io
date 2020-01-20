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
  - image_path: /images/data_analysis_projects/neuralnetworkmlpencoder/neuralnetworkmlpencoder_img02.jpg
    title: "Figure 3 - Simultaneous Calculations for the Input to the hidden layer from all 4 input patterns"
    weight: 3    
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


*y = (W1’ * input) + Bias_J*

These Weights and Bias were used to influence the system later when training it. The hidden layer then passed its values as Input to the Outer layer (layer K).

For the output layer (layer K), to use the values from the hidden layer, hidden layer values were passed through an activation function (sigmoid function). Using dot product expression for Element-wise calculation:

*Out_J = 1./(1+exp(-y))*

Sigmoid function was used to determine if the node’s output activates (fires) or not to influence its following node. The input values to layer K nodes were also multiplied with a different set of their corresponding Weights (W2) summed up and then added to another set of Bias (Bias_K).

*Out_K = (W2' * Out_J) + Bias_K*

The resulting values were the outputs for layer K and the system. These outputs were then compared to the Desired Output pattern (Target Output) and calculating the difference between the two to determine the Error.

*Error = Actual Output – Target Output*

Error Back-Propagation (EBP) was then used to make the adjustments to the Weights and Bias to reduce the Error in turn training the system to work as desired.

The influence of changes in the Weights (W1 and W2) were determined through partial derivation of the functions of the Forward propagation of the system.

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 2 %}
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

Small delta k (𝛿<sub>K</sub>) for each node of layer K was determined by the expression:

*𝛿<sub>k</sub> = O<sub>k</sub> * (1 – O<sub>k</sub>) (O<sub>k</sub> – t<sub>k</sub>)*

were OK was the Actual Output and t<sub>k</sub> was the Target Output of that specific node. Changes for weights (W2) between layer J and K (W<sub>jk</sub>) were then calculated by the expression:

*𝛿E / 𝛿W<sub>jk</sub> = O<sub>j</sub> 𝛿<sub>k</sub>*

were O<sub>j</sub> was the output from the previous node (hidden layer). Small delta j (𝛿<sub>j</sub>) for each node of layer J was determined by the expression:

*𝛿<sub>j</sub> = O<sub>j</sub> * (1 – O<sub>j</sub>) * ∑ 𝛿<sub>k</sub> W<sub>jk</sub>*

were O<sub>j</sub> was the output from hidden layer (layer J) and ∑𝛿<sub>k</sub> W<sub>jk</sub> was the sum of all layer K nodes connected to corresponding layer J node. Changes for weights (W1) between layer I and J (W<sub>ij</sub>) were then calculated by the expression:

*𝛿E / 𝛿W<sub>ij</sub> = O<sub>i</sub> 𝛿<sub>j</sub>*

were O<sub>i</sub> was the outputs from the input layer (layer I) nodes connected to that node of layer J. The weights (W1 and W2) were then updated (replaced) using expressions:

<span class="custom-tablecaption">Table 2: Expressions used to update the values of weights W1 and W2</span>

| Weights  | Weight Updating Expression |
| ------------- | :--------------------: |
| W2 (W<sub>jk</sub>) | W<sub>jk</sub> = W<sub>jk</sub> + (- learning rate * O<sub>j</sub> 𝛿<sub>k</sub>) |
| W1 (W<sub>ij</sub>) | W<sub>ij</sub> = W<sub>ij</sub> + (- learning rate * O<sub>i</sub> 𝛿<sub>J</sub>) |

Bias had a simpler expression to differentiate as it was just treated as an output of 1 and its updating expression was given by small delta l (𝛿l) of that layer:

*𝛿E / 𝛿θ = 𝛿<sub>l</sub>*

<span class="custom-tablecaption">Table 3: Expressions used to update the values of Bias_J and Bias_K</span>

| Bias  | Bias Updating Expression |
| ------------- | :--------------------: |
| Bias_K (layer K) | Bias_K = Bias_K + (- learning rate * 𝛿<sub>k</sub>) |
| Bias_J (layer J) | Bias_J = Bias_J + (- learning rate * 𝛿<sub>j</sub>) |

The process was then carried out for the different input and desired output pattern pairs through multiple iterations, using gradient decent to adjust the weights and bias values towards a low Error function.

### Initialization of weights in MATLAB

To utilise the vector calculations of MATLAB the weights were stored in matrix form. Weights W1 (between layer I and layer J) were initialised into a 4x2 matrix while Weights W2 (between layer J and layer K) were initialised as 2x4 matrix.

| W1 matrix |        |
| ---- | ---- |
| W<sub>11</sub> | W<sub>12</sub> |
| W<sub>21</sub> | W<sub>22</sub> |
| W<sub>31</sub> | W<sub>32</sub> |
| W<sub>41</sub> | W<sub>42</sub> |  

| W2 matrix |    |    |    |  
| ---- | ---- | ---- | ---- |
| W<sub>11</sub> | W<sub>12</sub> | W<sub>13</sub> | W<sub>14</sub> |
| W<sub>21</sub> | W<sub>22</sub> | W<sub>23</sub> | W<sub>24</sub> |

The matrices were initialised using the function “rand()” to generate uniformly distributed random numbers in the interval (0,1) for both matrices.

Bias (Bias_J and Bias_K) were also initialised in a similar way, however, using the function “zeros()” to initialise them as zeros. Bias_J (between layer I and layer J) and Bias_K (between layer J and layer K).

| Bias_J vector |                                                         
| ---- |
| b<sub>11</sub> |
| b<sub>21</sub> |

| Bias_K vector |
| ---- |
| b<sub>11</sub> |
| b<sub>21</sub> |
| b<sub>31</sub> |
| b<sub>41</sub> |

### Forward propagation in MATLAB

To further take advantage of MATLAB’s capabilities, a parallel approach to carrying out the forward propagation was adopted in the MATLAB code. By carrying out large matrix multiplications instead of running each instance of passing a single input and output pattern through the encoder through an internal loop, all patterns could be carried out simultaneously (Neural Network Tutorial 2014).

For the input y to the hidden layer J, given by the expression:


*y = (W1’ * input) + Bias_J;*

<ul class="photo-gallery">
  {% for image in page.images %}
    {% if image.weight == 3 %}
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

The results from multiplying the transposed W1 weights matrix with a 4x4 matrix (each input pattern as a column vector) was a 2x4 matrix with each column being the results that would have been from carrying out each pattern one at a time and summing them up. That is for example in Input pattern 1 (1,0,0,0):

*W<sub>11</sub> * 1 + W<sub>21</sub> * 0 + W<sub>31</sub> * 0 + W<sub>41</sub> * 0 + b<sub>11</sub> = R1,1 (Input y for top node in pattern 1)*

*W<sub>12</sub> * 1 + W<sub>22</sub> * 0 + W<sub>32</sub> * 0 + W<sub>42</sub> * 0 + b<sub>21</sub> = R2,1 (Input y for bottom node in pattern 1)*

In doing this all the calculations for the other input patterns were carried out at the same time.

Because the values of the output converge to 0 and 1 but never equal to them 0.9 and 0.1 were used instead.

The 1 in the Bias part of the calculation was omitted (1 * Bias_J) as the Bias were added on to the expression “y = W1’ * input” but since they were initialised as zeros they would not have much of an impact during the first iteration. This was also done for Bias_K in computing the input to the outer layer.

The parallel matrix calculations demonstrated in Figure 3 (simultaneous calculations for the Input to the hidden layer from all 4 input patterns) was maintained for the other stages of the forward propagation. That is in calculating output from the hidden layer using expression “*Out_J = 1./(1+exp(-y))*” and Input to the outer layer using expression “*Out_K = (W2' * Out_J) + Bias_K.*”.

### Back-propagation of error in MATLAB

The Error matrix (difference between the output results and the desired output results) was computed for all the training input patterns by expression:

*Error = Actual Output – Target Output*

The Error matrix was then used to compute the values for the small deltak (𝛿k) for all the training input patterns by expression:

```math
deltak = Error.* (Out_K.* (1 - Out_K));
```
Small deltaj was computed by the expression:

```math
deltaj = (W2* deltak).* (Out_J.* (1 - Out_J));
```

To compute big DELTA_K and DELTA_J, extractions had to be made in the larger matrices for all the input pattern calculations of Out_J matrix with deltak matrix and input matrix with deltaj matrix respectively. This was possible because the values of columns 1 of Out_J and deltak corresponded to the calculations of Input pattern 1 (1,0,0,0), those of column 2 to input pattern 2 (0,1,0,0), column 3 for input pattern 3 (0,0,1,0) and column 4 for input pattern 4 (0,0,0,1). This was the same for deltaj matrix and input matrix.

Instead of a loop to cycle and extract the 4 different input pattern data separately, a simple range function was used on the matrix to specify and extract the column data needed for the four DELTA_K’s. Example:  


*DELTA_K1 = Out_J(:,1) * deltak(:,1)';*

For Input pattern 1 data. This was repeated four times substituting the value 1 for the number that corresponded to the input pattern column we desired and storing them in 2x4 matrix for DELTA_K1, DELTA_K2, DELTA_K3 and DELTA_K4.

The same process was done for DELTA_J using the expressions:


*Tran_DELTA_J1 = deltaj(:,1) * input(:,1)';*

*DELTA_J1 = Tran_DELTA_J1';*

For Input pattern 1 data. Repeating the value change to get 4x2 matrices for DELTA_J1, DELTA_J2, DELTA_J3 and DELTA_J4.

The resulting matrices DELTA_K and DELTA_J were the gradient adjustments needed for matrices W1 and W2 in this current iteration of the Error Back-Propagation of the multi-layer perceptron (MLP) 4-2-4 encoder.

The adjustments for the Bias (Bias_J and Bias_K) were stored in a similar way and since the bias adjustments were the small deltas of that layer given by expression:

*𝛿E / 𝛿θ = 𝛿<sub>l</sub>*

<span class="custom-tablecaption">Table 4: Bias_K and Bias_J gradient adjustment values for the different input patterns</span>

| Input Pattern | Bias_K adjustments matrix | Bias_J adjustments matrix |
| ------------- | ------------------------- | ------------------------- |
| [1,0,0,0]<sup>T</sup> |	Bias_K1 = deltak(:,1)	| Bias_J1 = deltaj(:,1) |
| [0,1,0,0]<sup>T</sup>	| Bias_K2 = deltak(:,2)	| Bias_J2 = deltaj(:,2) |
| [0,0,1,0]<sup>T</sup>	| Bias_K3 = deltak(:,3)	| Bias_J3 = deltaj(:,3) |
| [0,0,0,1]<sup>T</sup>	| Bias_K4 = deltak(:,4)	| Bias_J4 = deltaj(:,4) |

### Updating of Weights and Bias

To update the weights W1 matrix for use in the next iteration, the four DELTA_K’s were added together:

*DELTA_K_SUM = DELTA_K1 + DELTA_K2 + DELTA_K3 + DELTA_K4;*

and then the new expression was used to adjust W2 weights:

*W2 = W2 + (learn_rate * DELTA_K_SUM);*

For weights W2 matrix, the matrix DELTA_J_SUM:

*DELTA_J_SUM = DELTA_J1 + DELTA_J2 + DELTA_J3 + DELTA_J4;*

was used to adjust W1 weights

*W1 = W1 + (learn_rate * DELTA_J_SUM);*

For the Bias (Bias_J and Bias_K), a similar procedure was carried out for:


*Bias_K_SUM = Bias_K1 + Bias_K2 + Bias_K3 + Bias_K4;*

*Bias_J_SUM = Bias_J1 + Bias_J2 + Bias_J3 + Bias_J4;*

To adjust the Bias_K and Bias_J respectively for the next iteration:

*Bias_K = Bias_K + (learn_rate * Bias_K_SUM);*

*Bias_J = Bias_J + (learn_rate * Bias_J_SUM);*


<h2 class="text-underline">Implementation</h2>

### Software
**MATLAB Code to Implement Neural Network MLP Encoder**
```matlab
%----------- Lab 4 � Neural Networks - Mini-Batch ------------------------%

%------------------ Instructor: Dr Peter Jancovic ------------%
%------------------ Written by:	James J Nkhata ---------------%

%-------------------------- HOUSE KEEPING --------------------------------%

clear variables; % Used to clear all the variables
                 % in the current work place.
close all; % Used to close all external windows.
clc; % Used to clear the Command Window on running the script.
%-------------------------------------------------------------------------%

%----------------------------- DEFINE UNITS ------------------------------%
% Input pattern - Columns as each training pattern
input = [0.9 0.1 0.1 0.1 % input 4x4 Matrix [1,0,0,0]--------------%
         0.1 0.9 0.1 0.1 %------------------[0,1,0,0]--------------%
         0.1 0.1 0.9 0.1 %------------------[0,0,1,0]--------------%
         0.1 0.1 0.1 0.9]; %----------------[0,0,0,1]--------------%

% Output pattern (Target) - Columns as each training pattern
Out_TRGT = [0.9 0.1 0.1 0.1 % Target output Out_TRGT 4x4 Matrix [1,0,0,0]-%
            0.1 0.9 0.1 0.1 %-----------------------------------[0,1,0,0]-%
            0.1 0.1 0.9 0.1 %-----------------------------------[0,0,1,0]-%
            0.1 0.1 0.1 0.9]; %---------------------------------[0,0,0,1]-%                    

% Intialising Weight Matrix W1 and W2 randomly %
% Create 4x2 matrix and intialise it with random values using a heuristic.
W1 = -0.5773 + (0.5773-(-0.5773)).*rand(4,2); % Create a 4x2 matrix using  
                                              % Xavier intialisation
                                              % sqrt(2/(Nj + Nk)).

W2 = rand(2,4);% Create a 2x4 matrix and intialise it with uniformly  
               % distributed random  numbers in the interval (0,1).

Bias_J = zeros(2,1); % Create a 2x1 matrix and initailise with
                    % zeros for Bias_J (Layer J - Hidden Layer).
Bias_K = zeros(4,1); % Create a 4x1 matrix and initailise with
                    % zeros for Bias_K (Layer K - Output Layer).                     

iterations = 100000; % Value used to set the number of iterations to
                     % run for training the system.

learn_rate = -.0001; % The value for learning rate is set by this variable.

N_Errors = (iterations);% A variable used to store the Error value for
                        % each iteration.
%-------------------------------------------------------------------------%

%---------------------- BEGIN THE TRAINING ITERATION(S) ------------------%
for n=1:1:iterations  

%----------------------- LEARN RATE ADJUSTMENTS --------------------------%
% Lines of conditional statements used to easy the effects of the
% learn_rate as the system increments through iterations.
if n >=20    
    learn_rate = -.001; % set learn_rate to -0.001.
elseif n >= 100
    learn_rate = -.001; % set learn_rate to -0.001.
elseif n >= 5000
    learn_rate = -.01; % set learn_rate to -0.01.
elseif n >= 50000
    learn_rate = -.1; % set learn_rate to -.1.    
end   

%----------------------- FORWARD PROPAGATION -----------------------------%

% INPUT TO THE HIDDEN LAYER
y = (W1' * input) + Bias_J; % Transpose W1 to align with input matrix
                            % and then add Bias_J matrix.

% OUTPUT FROM THE HIDDEN LAYER %
Out_J = 1./(1+exp(-y)); % Output of the hidden layer is the sigmoid
                        % normalization function of y (dot product
                        % to multiply with the vector).

% INPUT TO THE OUTER LAYER %        
Out_K = (W2' * Out_J) + Bias_K; % Transpose W2 matrix to align with Out_J
                                % matrix and then add Bias_K matrix to get  
                                % the Out_K (Actual Output).

%----------------------- ERROR BACK-PROPAGATION --------------------------%
% CALCULATE THE ERROR (ACTUAL OUTPUT - TARGET OUTPUT) OF ENCODER %
Error = Out_K  - Out_TRGT; % Difference between the Actual Output matrix
                           % and the Target Output matrix.

Sum_Error = (sumsqr(Error))/2; %  ?(Actual Output � Target Output)^2 / 2.

% Generate N_Errors matrix for  n (iterations) vs Error %
N_Errors(n,1) = n; % store values of n in the first column of the matrix.
N_Errors(n,2) =  Sum_Error;% store Error values for each iteration of n
                           % in the first column of the matrix.

% Small delta k (deltak) is calculated for output layer
deltak = Error.* (Out_K.*(1 - Out_K)); % Each Element of the Error is
                                        % multiplied by the sigmoid
                                        % dervative of that particular
                                        % node using Element-wise(.*).  

% Small delta j (deltaj) is calculated for hidden layer
deltaj = (W2 * deltak).*(Out_J.*(1 - Out_J)); % Each Element of the Error  
                                            % is multiplied by the layer J
                                            % dervative of that particular
                                            % node using Element-wise(.*).

%----------------------- WEIGHT AND BIAS ADJUSTMENTS ---------------------%                                        
% Pick out Columns of Out_J with deltak matrix for DELTA_K and input matrix
% with deltaj for DELTA_J. The column picked corresponds to the training
% input pattern. Column 1 to input pattern 1 (0,1,0,0), those of column 2  
% to input pattern 2(0,1,0,0), column 3 for input pattern 3 (0,0,1,0) and  
% column 4 for input pattern 4 (0,0,0,1).

% Input pattern 1 (1,0,0,0)
DELTA_K1 = Out_J(:,1) * deltak(:,1)';%DELTA_K for Input pattern (1,0,0,0).
Tran_DELTA_J1 = deltaj(:,1) * input(:,1)'; % transpose to 4x2 to match W1.
DELTA_J1 = Tran_DELTA_J1'; % DELTA_J for Input pattern (1,0,0,0).

% Input pattern 2 (0,1,0,0)
DELTA_K2 = Out_J(:,2) * deltak(:,2)';%DELTA_K for Input pattern (0,1,0,0).
Tran_DELTA_J2 = deltaj(:,2) * input(:,2)'; % transpose to 4x2 to match W1.
DELTA_J2 = Tran_DELTA_J2'; % DELTA_J for Input pattern (0,1,0,0).

% Input pattern 3 (0,0,1,0)
DELTA_K3 = Out_J(:,3) * deltak(:,3)';%DELTA_K for Input pattern (0,0,1,0).
Tran_DELTA_J3 = deltaj(:,3) * input(:,3)'; % transpose to 4x2 to match W1.
DELTA_J3 = Tran_DELTA_J3'; % DELTA_J for Input pattern (0,0,1,0).

% Input pattern 4 (0,0,0,1)
DELTA_K4 = Out_J(:,4) * deltak(:,4)';%DELTA_K for Input pattern (0,0,0,1).
Tran_DELTA_J4 = deltaj(:,4) * input(:,4)'; % transpose to 4x2 to match W1.
DELTA_J4 = Tran_DELTA_J4'; % DELTA_J for Input pattern (0,0,0,1).

Bias_K1 = deltak(:,1);  Bias_J1 = deltaj(:,1); % Store (1,0,0,0) Bias.
Bias_K2 = deltak(:,2);  Bias_J2 = deltaj(:,2); % Store (0,1,0,0) Bias.
Bias_K3 = deltak(:,3);  Bias_J3 = deltaj(:,3); % Store (0,0,1,0) Bias.
Bias_K4 = deltak(:,4);  Bias_J4 = deltaj(:,4); % Store (0,0,0,1) Bias.

%---------------------- CALCULATE THE DELTA SUMS -------------------------%
% Sum up the values for DELTA_K and the values of DELTA_J
DELTA_K_SUM = DELTA_K1 + DELTA_K2 + DELTA_K3 + DELTA_K4; % DELTA_K_SUM.
DELTA_J_SUM = DELTA_J1 + DELTA_J2 + DELTA_J3 + DELTA_J4; % DELTA_J_SUM.

%---------------------- CALCULATE THE BIAS SUMS --------------------------%
% Sum up the values for DELTA_K and the values of DELTA_J
Bias_K_SUM = Bias_K1 + Bias_K2 + Bias_K3 + Bias_K4; % Bias_K_SUM.
Bias_J_SUM = Bias_J1 + Bias_J2 + Bias_J3 + Bias_J4; % Bias_J_SUM.

%-------------------------------------------------------------------------%

%----- UPDATE THE WEIGHTS USING DELTA SUM, BIAS SUM AND LEARNING RATE ----%

W2 = W2 + (learn_rate * DELTA_K_SUM); % Update W2 weights matrix.
W1 = W1 + (learn_rate * DELTA_J_SUM); % Update W1 weights matrix.
Bias_K = Bias_K + (learn_rate * Bias_K_SUM); % Update Bias_K vector.
Bias_J = Bias_J + (learn_rate * Bias_J_SUM); % Update Bias_J vector.
%-------------------------------------------------------------------------%

end
%----------------------- END THE TRAINING ITERATION(S) -------------------%    
%-------------------------------------------------------------------------%

%--------------- PLOT ERROR AS FUNCTION OF n (iterations) ----------------%
plot (N_Errors(:,1), N_Errors(:,2), 'r'); % Plot column 1 (n) vs column 2
                                          % (Errors)for each iteration
                                          % using a red line.
xlabel('n - iterations'); % Label for the X-axis.
ylabel('Error'); % Label for the X-axis.
title('Error as a Function of n (iterations)'); % Title of the graph.


%----------------------- COMMAND WINDOW PRINT OUTS -----------------------%

%--------------------- Print Trained System Results ----------------------%

fprintf('------- Trained System Results -------\n\n');
fprintf('Number of Iterations : ');
disp(iterations);
fprintf('Learning Rate: ');
disp(learn_rate);
fprintf('Trained Bias J:\n');
disp(Bias_J);
fprintf('Trained Bias K:\n');
disp(Bias_K);
fprintf('Trained W1:\n');
disp(W1);
fprintf('Trained W2:\n');
disp(W2);
fprintf('Trained Encoder Output:\n');
disp(Out_K);
fprintf('Final Error: ');
disp(Sum_Error);

fprintf('------- End of System Results -------');
%-------------------------------------------------------------------------%    

```
<h2 class="text-underline">Conclusion</h2>
