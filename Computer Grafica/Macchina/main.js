angle = 0.0;

function createObjectBuffers(gl, obj){
   //crea il buffer per l'oggetto
   //equivale a var posBuffer = ...
   obj.vertexBuffer = gl.createBuffer();
   gl.bindBuffer(gl.ARRAY_BUFFER, obj.vertexBuffer);
   gl.bufferData(gl.ARRAY_BUFFER, obj.vertices, gl.STATIC_DRAW);
   gl.bindBuffer(gl.ARRAY_BUFFER, null);
    
   //buffer degli indici
   obj.indexBuffer = gl.createBuffer();
   gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, obj.indexBuffer);
   gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, obj.triangleIndices, gl.STATIC_DRAW);
   gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
};

function drawObject(gl, obj, fillColor){  
   gl.bindBuffer(gl.ARRAY_BUFFER, obj.vertexBuffer);
   gl.enableVertexAttribArray(this.simpleShader.aPositionIndex);
   gl.vertexAttribPointer(this.simpleShader.aPositionIndex, 3, gl.FLOAT, false, 0, 0);
    
   gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, obj.indexBuffer);
   //(location, valore)
   gl.uniform3fv(this.simpleShader.uColorLocation, fillColor);
   gl.drawElements(gl.TRIANGLES, obj.triangleIndices.length, gl.UNSIGNED_SHORT, 0);
  
  
   gl.disableVertexAttribArray(this.simpleShader.aPositionIndex);
   gl.bindBuffer(gl.ARRAY_BUFFER, null);
};

function setupWebGL(){
   canvas = document.getElementById("OUTPUT-CANVAS");
   gl = canvas.getContext('webgl');
}

function setupWhatToDraw(){
   //crea gli oggetti grazie alle funzioni precedenti
   cube = new Cube(10);
   createObjectBuffers(gl, cube);
    
   cylinder = new Cylinder(10);
   createObjectBuffers(gl, cylinder);
}

function setupHowToDraw(){
   simpleShader = new simpleShader(gl);
}

function draw(){
   //DEPTH_TEST = fa in modo che i triangoli si renderizzino
   //alla corretta profondità (quelli più vicini coprono quelli dietro)
   gl.enable(gl.DEPTH_TEST);
   angle += 0.01;

   //sfondo
   gl.clearColor(0.8,0.8,0.8,1.0);
   gl.clear(gl.COLOR_BUFFER_BIT,gl.DEPTH_BUFFER_BIT);

   //setup the view transform
   view_transform = glMatrix.mat4.create();
   //posizione camera
   glMatrix.mat4.lookAt(view_transform,[0.0,2.0,10.0],[0.0,0.0,0.0],[0,1,0]);

   // setup the projection transform
   projection_transform = glMatrix.mat4.create();
   //matrice4x4, fov verticale, aspect ratio, lunghezza piano vicino, " lontano
   glMatrix.mat4.perspective(projection_transform, 3.14/4.0, 1.0, 0.01, 150000000000000);

   //rotation around Y
   rotate_transform = glMatrix.mat4.create();
   glMatrix.mat4.fromRotation(rotate_transform,angle,[0.0,1.0,0.0]);

   //uso il simpleShader
   gl.useProgram(simpleShader);

   //implemento le trasformazioni precedenti
   gl.uniformMatrix4fv(simpleShader.uProjectionMatrixLocation, false, projection_transform);
   gl.uniformMatrix4fv(simpleShader.uViewMatrixLocation, false, view_transform);
   gl.uniformMatrix4fv(simpleShader.uRotationMatrixLocation, false, rotate_transform);

   //scaling matrice
   scale_matrix = glMatrix.mat4.create();
   glMatrix.mat4.fromScaling(scale_matrix,[0.1,0.1,0.1]);
    
   translate_matrix = glMatrix.mat4.create();
   axis_matrix = glMatrix.mat4.create();

   //per ogni vertice del triangolo
   for(var i=0; i < 3; ++i){
      var color_translate = [0.0,0.0,0.0];
      var scaling = [0.01,0.01,0.01]; 

      color_translate[i] = 1.0;
      scaling[i] = 2;

      //Crea una matrice da un vettore di scaling
      glMatrix.mat4.fromScaling(scale_matrix,scaling);
      //Crea una matrice da un vettore di traslazione
      glMatrix.mat4.fromTranslation(translate_matrix,color_translate);
      //Moltiplica le due matrici
      glMatrix.mat4.mul(translate_matrix,translate_matrix,scale_matrix);

      //location, trasposta (si/no), valore
      gl.uniformMatrix4fv(simpleShader.uM,false,translate_matrix);
      drawObject(gl,cube,color_translate);
   }

   /* *************************************************************************************/
   //Setup delle matrici di trasformazione e le chiamate al renderer
   //per renderizzare la macchina
   gl.uniformMatrix4fv(simpleShader.uM,false,glMatrix.mat4.create());

   //Creo la matrice per la macchina
   M = glMatrix.mat4.create();
   //Posizione macchina
   glMatrix.mat4.fromTranslation(translate_matrix,[0,1.5,1]);
   //Dimensioni macchina
   glMatrix.mat4.fromScaling(scale_matrix,[0.7,0.25,1]);
   glMatrix.mat4.mul(M,scale_matrix,translate_matrix);
   glMatrix.mat4.fromRotation(rotate_transform,0.0,[1,0,0]);

   glMatrix.mat4.mul(M,rotate_transform,M);
   glMatrix.mat4.fromTranslation(translate_matrix,[0,0.1,-1]);
   glMatrix.mat4.mul(M,translate_matrix,M);

   gl.uniformMatrix4fv(simpleShader.uM,false,M);
   drawObject(gl,cube,[0.5,0.5,0.5]);


   //Disegna le ruote (cilindri)
   //Ruota di diametro 2*0.2 = 0.4 centrata nell'origine
   glMatrix.mat4.fromRotation(rotate_transform,3.14/2,[0,0,1]);
   glMatrix.mat4.fromTranslation(translate_matrix,[1,0,0]);
   glMatrix.mat4.mul(M,translate_matrix,rotate_transform);
    
   glMatrix.mat4.fromScaling(scale_matrix,[0.1,0.2,0.2]);
   glMatrix.mat4.mul(M,scale_matrix,M);

    
   M1 = glMatrix.mat4.create();
   
   //Ruota #1 
   glMatrix.mat4.fromTranslation(translate_matrix,[-0.8,0.2,-0.7]);
   glMatrix.mat4.mul(M1,translate_matrix,M);
   gl.uniformMatrix4fv(simpleShader.uM,false,M1); 
   drawObject(gl,cylinder,[1.0,0.6,0.5]);

   //Ruota #2
   glMatrix.mat4.fromTranslation(translate_matrix,[0.8,0.2,-0.7]);
   glMatrix.mat4.mul(M1,translate_matrix,M);
   gl.uniformMatrix4fv(simpleShader.uM,false,M1); 
   drawObject(gl,cylinder,[1.0,0.6,0.5]);

    /* this will increase the size of the wheel to 0.4*1,5=0.6 */
    //glMatrix.mat4.fromScaling(scale_matrix,[1,1.5,1.5]);;
    //glMatrix.mat4.mul(M,scale_matrix,M);

   //Ruota #3
   glMatrix.mat4.fromTranslation(translate_matrix,[0.8,0.2,0.7]);
   glMatrix.mat4.mul(M1,translate_matrix,M);
   gl.uniformMatrix4fv(simpleShader.uM,false,M1); 
   drawObject(gl,cylinder,[1.0,0.6,0.5]);

   //Ruota #4
   glMatrix.mat4.fromTranslation(translate_matrix,[-0.8,0.2,0.7]);
   glMatrix.mat4.mul(M1,translate_matrix,M);
   gl.uniformMatrix4fv(simpleShader.uM,false,M1); 
   drawObject(gl,cylinder,[1.0,0.6,0.5]);

   window.requestAnimationFrame(draw);
}

function setup(){
   setupWebGL();
   setupWhatToDraw();
   setupHowToDraw();
}

function helloRotations(){
   setup();
   draw();
}

window.onload = helloRotations;