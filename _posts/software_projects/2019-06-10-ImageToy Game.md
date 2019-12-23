---
title: "ImageToy Game"
date: 2019-06-10
categories: [software-projects]
permalink: /:categories/:title/
feature_img: /images/software_projects/imagetoygame/imagetoygame_img00.jpg
excerpt: "imagetoy, python, game, tkinter, software, pil, math, random"
purpose: "This assignment was about implementing a graphical user interface to create an ImageToy game. This was an electronic version of an old children’s game, which re-created a jumbled up picture by moving one piece at a time."
toc: true
classes: wide
images:
  - image_path: /images/software_projects/imagetoygame/imagetoygame_img01.jpg
    title: "Figure 1 - Open a Jpeg or Png file"
    weight: 1
  - image_path: /images/software_projects/imagetoygame/imagetoygame_img02.jpg
    title: "Figure 2 - Image Loaded"
    weight: 2
  - image_path: /images/software_projects/imagetoygame/imagetoygame_img03.jpg
    title: "Figure 3 - Image Shuffled (On difficulty 2)"
    weight: 3   
  - image_path: /images/software_projects/imagetoygame/imagetoygame_img04.jpg
    title: "Figure 4 - Puzzle Completed"
    weight: 4  
---
This assignment was about implementing a graphical user interface to create an ImageToy game. This was an electronic version of an old children’s game, which re-created a jumbled up picture by moving one piece at a time.

<h2 class="text-underline">Purpose</h2>

The aim of the assignment was to implement the ImageToy game as a Python application. The application was supposed to be able to load any image stored as a gif or jpeg file and display it. The user was required to enter the number of pieces in which to shuffle the image. The application would then randomly shuffle all of the pieces of the image. The number of pieces in the shuffled image, and hence the difficulty of reconstructing the image, was left as a user choice. It needed to make it possible to ‘unshuffle’ the shuffled image back to its original form by moving image blocks into the adjacent gap.

Finally, it was supposed to allow the user to play the game by clicking on pieces to move them. Clearly, only if the user clicks on a piece adjacent to the gap was the piece be moved. It was required as part of the assignment to avoid having to store the original image and its shuffled version as separate images as this was very inefficient.

<h2 class="text-underline">Implementation</h2>

### Software
This section shows a snippet of the python file (main.py) that was used to implement the game. Full code available from <a class="custom_link" href="https://github.com/jamesjrnkhata/ImageToy-game">GitHub</a> page.  

**"Main.py" Code Snippet**
```python

# ----------------------------------- GUI FUNCTION DEFINITIONS --------------------------------------------------- #

  # FUNCTION USED TO BROWSE FOR JPEG AND GIF IMAGES
  def file_browser(self):

      # open file through dialog box that only accepts jpeg and gif images
      # https://stackoverflow.com/questions/44403566/add-multiple-extensions-in-one-filetypes-mac-tkinter-filedialog-askopenfilenam
      self.filename = filedialog.askopenfilename(initialdir="/", title="Select file",
                                                 filetypes=[("jpeg / gif files", "*.gif *.jpg")])
      if self.filename != "":
          self.image = Image.open(self.filename)
          self.square_image = self.image.resize((800, 800))  # resize image to a square grid of 800 x 800
          self.square_image.save('saved_image.gif')
          self.label_image = PhotoImage(file='saved_image.gif')
          self.Display_label.configure(image=self.label_image)
          self.Display_label.grid()

  # FUNCTION USED TO LOOP THROUGH THE IMAGE_TILE_LIST ITERATOR
  # https://stackoverflow.com/questions/49916944/how-to-use-python-tkinter-to-iterate-images#
  def next_img(self):
      try:
          self.img = next(self.images)  # get the next image from the iterated image_tile_list
      except StopIteration:
          return  # if there are no more images, do nothing

  # FUNCTION USED TO INTIALIZEE THE TILE / IMAGE GRIDS RANDOMIZING
  def randomize_tiles(self):
      for _ in range(self.passed_value*2):
          # condition used to prevent random row and column values exceeding the edges of the 4 grid area
          if self.last_blank_row-1 >= 0 and self.last_blank_column-1 >= 0:
              rand_row = self.last_blank_row - 1
              rand_col = self.last_blank_column - 1
              times = random.randint(1, 3)  # generate a random number between 1 - 3 to perform the rotate_grid_area
              self.rotate_grid_area(times, rand_row, rand_col)

          # ADD COMPLEXITY TO THE RANDOMIZING OF THE TILES BY UNCOMMENTING
          # condition used to add more complexity to the randomizing_tiles (NOT FULLY DEBUGGED)
          #elif self.last_blank_row+1 < self.passed_value-1 and self.last_blank_column+1 < self.passed_value-1:
              #rand_row = self.last_blank_row - 1
              #rand_col = self.last_blank_column
              #times = random.randint(1, 3)  # generate a random number between 1 and 3
              #self.rotate_grid_area(times, rand_row, rand_col)

          else:
              pass  # do nothing

  # FUNCTION USED TO RANDOMIZIE INTERNALLY BY ROTATING THE TILES / IMAGE GRIDS
  def rotate_grid_area(self, times, r_row, r_col):

      for _ in range(times):
          # rotate entries in the grid area clockwise starting from first position (row=rand_row, column=rand_col)
          # pos1 is row=0,col=0; pos2 is row=0,col=0+1; pos3 is row=0+1,col=0+1; pos4 is row=0+1,col=0 entries
          # pos1 is relative to rand_row and rand_col
          pos1 = self.buttons[r_row][r_col].value_working  # access number entry in .value_working and assign to pos1
          imag1 = self.buttons[r_row][r_col].image  # access image entry in .image and assign to pos1

          pos2 = self.buttons[r_row][r_col+1].value_working  # access number entry in .value_working and assign to pos2
          imag2 = self.buttons[r_row][r_col+1].image  # access image entry in .image and assign to pos2

          pos3 = self.buttons[r_row+1][r_col+1].value_working  # access number entry in .value_working and assign to pos3
          imag3 = self.buttons[r_row+1][r_col+1].image  # access image entry in .image and assign to pos3

          pos4 = self.buttons[r_row+1][r_col].value_working  # access number entry in .value_working and assign to pos4
          imag4 = self.buttons[r_row+1][r_col].image  # access image entry in .image and assign to pos4

          # tile 4 moved to tile 1
          # condition to check if the value in pos4 belongs to the blank image tile
          if pos4 == self.buttons[self.last][self.last].value_solution:
              self.last_blank_row = r_row  # if true then set the new last_blank_row to rand_row
              self.last_blank_column = r_col  # if true then set the new last_blank_column to rand_column
          self.buttons[r_row][r_col].value_working = pos4  # change the value of pos1 to that of pos4
          self.buttons[r_row][r_col].image = imag4  # change the image of pos1 to that of pos4
          self.buttons[r_row][r_col].configure(image=imag4)  # change the image to new image

          # tile 1 moved to tile 2
          # condition to check if the value in pos1 belongs to the blank image tile
          if pos1 == self.buttons[self.last][self.last].value_solution:
              self.last_blank_row = r_row  # if true then set the new last_blank_row to rand_row
              self.last_blank_column = r_col+1  # if true then set the new last_blank_column to rand_column + 1
          self.buttons[r_row][r_col+1].value_working = pos1  # change the value of pos2 to that of pos1
          self.buttons[r_row][r_col+1].image = imag1  # change the image of pos2 to that of pos1
          self.buttons[r_row][r_col+1].configure(image=imag1)  # change the image to new image

          # tile 2 moved to tile 3
          # condition to check if the value in pos2 belongs to the blank image tile
          if pos2 == self.buttons[self.last][self.last].value_solution:
              self.last_blank_row = r_row+1  # if true then set the new last_blank_row to rand_row + 1
              self.last_blank_column = r_col+1   # if true then set the new last_blank_column to rand_column + 1
          self.buttons[r_row+1][r_col+1].value_working = pos2  # change the value of pos3 to that of pos2
          self.buttons[r_row+1][r_col+1].image = imag2  # change the image of pos3 to that of pos2
          self.buttons[r_row+1][r_col+1].configure(image=imag2)  # change the image to new image

          # tile 3 moved to tile 4
          # condition to check if the value in pos3 belongs to the blank image tile
          if pos3 == self.buttons[self.last][self.last].value_solution:
              self.last_blank_row = r_row+1  # if true then set the new last_blank_row to rand_row + 1
              self.last_blank_column = r_col   # if true then set the new last_blank_column to rand_column
          self.buttons[r_row+1][r_col].value_working = pos3  # change the value of pos4 to that of pos3
          self.buttons[r_row+1][r_col].image = imag3  # change the image of pos4 to that of pos3
          self.buttons[r_row+1][r_col].configure(image=imag3)  # change the image to new image

```

<h2 class="text-underline">Gallery</h2>

<ul class="photo-gallery-2col">
  {% for image in page.images %}
    {% if image.weight >= 1 and image.weight <= 2 %}
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

<ul class="photo-gallery-2col">
  {% for image in page.images %}
    {% if image.weight >= 3 and image.weight <= 4 %}
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

Full code available from <a class="custom_link" href="https://github.com/jamesjrnkhata/ImageToy-game">GitHub</a> page (<a class="custom_link" href="https://github.com/jamesjrnkhata/ImageToy-game">ImageToy-game</a>).
