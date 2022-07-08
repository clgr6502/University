const glsl = x => x;

uniformShader = function(gl) {
  var vertexShaderSource = glsl`
    uniform   mat4 uModelViewMatrix;
    uniform   mat4 uProjectionMatrix;
    uniform   mat4 uViewMatrix;

    //Fari macchina
    uniform mat4 uInverseViewMatrix;
   
    //Posizione del vertice
    attribute vec3 aPosition; 
    attribute vec3 aNormal;
    attribute vec2 aTextureCoords;

    //Normale in view space
    varying vec3 vViewSpaceNormal;
    varying vec3 vViewSpaceViewDirection;

    //Direzione spotlight e coordinate texture
    varying vec3 vPosVS;
    varying vec3 vVSSpotlightDirection;
    varying vec2 vTextureCoords;

    //Coordinate in clip space dei fari
    varying vec4 vPosition;


    void main(void){
      gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aPosition, 1.0);

      //Normalizzazione per illuminazione Phong
      vViewSpaceNormal = normalize(uModelViewMatrix * vec4(aNormal, 0.0)).xyz;
      vViewSpaceViewDirection = -normalize(uModelViewMatrix * vec4(aPosition, 1.0)).xyz;

      //Posizione in VS da Object a View
      vPosVS = (uModelViewMatrix * vec4(aPosition, 1.0)).xyz;
      
      //Calcolo la direzione dei fari
      vVSSpotlightDirection = normalize(uViewMatrix * vec4(0.0, -1.0, 0.0, 0.0)).xyz;
      vTextureCoords = aTextureCoords;

      mat4 modelMatrix = uInverseViewMatrix * uModelViewMatrix; //non passo la model matrix, la calcolo

      //Posizione vertice in world space
      vPosition = modelMatrix * vec4(aPosition, 1.0); 
    }
  `;

  var fragmentShaderSource = glsl`
    precision highp float;

    uniform vec4 uColor;
    //Attivo la texture
    uniform sampler2D uSampler;
    uniform int uTexturesEnabled;

    //Per illuminazione Phong
    uniform vec3 uViewSpaceLightDirection;
    varying vec3 vViewSpaceNormal;
    varying vec3 vViewSpaceViewDirection;
    varying vec3 vPosVS;

    varying vec2 vTextureCoords;

    //Per lo spotlight
    //Posizioni spotlight in world
    uniform vec3 uSpotlights[12];
    varying vec3 vVSSpotlightDirection;
    
    //Coordinate texture dei fari
    uniform sampler2D uHeadlightSampler;

    //Trasformazione fari a clip space dei fari
    uniform mat4 uHeadlightDxMatrix;
    uniform mat4 uHeadlightSxMatrix;

    //Shadow map
    uniform sampler2D uHeadlightSx;
    uniform sampler2D uHeadlightDx;

    varying vec4 vPosition;

    void main(void){
      
      //Controllo se le texture sono abilitate
      vec3 color;
      if(uTexturesEnabled > 0){
        color = texture2D(uSampler, vTextureCoords).xyz;
      }else{
        color = uColor.xyz;
      }
      
      //Calcolo luminosità
      float diffuseLight = max(dot(uViewSpaceLightDirection, vViewSpaceNormal), 0.0)
      * 0.5 + 0.5;
      vec3 diffuseColor = color * diffuseLight;

      //Luce che si riflette rispetto alla normale
      vec3 reflectedLightDirection = -uViewSpaceLightDirection + 2.0 * 
      dot(uViewSpaceLightDirection, vViewSpaceNormal) * vViewSpaceNormal;

      //Luce speculare
      float specularLight = max(0.0, pow(dot(vViewSpaceViewDirection, reflectedLightDirection), 1.0));
      vec3 specularColor = color * specularLight; //colore del riflesso è della texture

      vec4 vHeadlightDxTextureCoords = (uHeadlightDxMatrix * vPosition);
      vec4 vHeadlightSxTextureCoords = (uHeadlightSxMatrix * vPosition);

      //Divido per la proiezione prospettica
      vHeadlightDxTextureCoords /= vHeadlightDxTextureCoords.w;
      vHeadlightSxTextureCoords /= vHeadlightSxTextureCoords.w;

      vHeadlightDxTextureCoords = vHeadlightDxTextureCoords * 0.5 + 0.5;
      vHeadlightSxTextureCoords = vHeadlightSxTextureCoords * 0.5 + 0.5;

      //Evitare peterpanning
      float slopeDependentBias = clamp(0.005 * 
      tan(acos(dot(vViewSpaceNormal, uViewSpaceLightDirection))), 0.0025, 0.1);

      vec4 headlightColorDx;
      //Se rientra nelle coordinate del faro (destro)
      if(vHeadlightDxTextureCoords.x >= 0.0 && vHeadlightDxTextureCoords.x <= 1.0 &&
         vHeadlightDxTextureCoords.y >= 0.0 && vHeadlightDxTextureCoords.y <= 1.0 &&
         vHeadlightDxTextureCoords.z >= 0.0 && vHeadlightDxTextureCoords.z <= 1.0){

        float depth = texture2D(uHeadlightDx, vHeadlightDxTextureCoords.xy).z;

        //Sono all'interno del cono luminoso = proietto
        if(depth + slopeDependentBias > vHeadlightDxTextureCoords.z){
          headlightColorDx = texture2D(uHeadlightSampler, vHeadlightDxTextureCoords.xy);
        }else{
          headlightColorDx = vec4(1.0,0.0,0.0,0.0);
        }
      }else{
        headlightColorDx = vec4(1.0,0.0,0.0,0.0);
      }

      vec4 headlightColorSx;
      if(vHeadlightSxTextureCoords.x >= 0.0 && vHeadlightSxTextureCoords.x <= 1.0 &&
         vHeadlightSxTextureCoords.y >= 0.0 && vHeadlightSxTextureCoords.y <= 1.0 &&
         vHeadlightSxTextureCoords.z >= 0.0 && vHeadlightDxTextureCoords.z <= 1.0){

        float depth = texture2D(uHeadlightSx, vHeadlightSxTextureCoords.xy).z;

        if(depth + slopeDependentBias > vHeadlightSxTextureCoords.z){ 
          headlightColorSx = texture2D(uHeadlightSampler, vHeadlightSxTextureCoords.xy);
        }else{
          headlightColorSx = vec4(1.0,0.0,0.0,0.0);
        }
      }else{
        headlightColorSx = vec4(1.0,0.0,0.0,0.0);
      }

      //Spotlights
      float spotlightLight = 0.0;
      for(int i = 0; i < 12; i ++){
        float tmplight = 0.5;
        float cosangle = dot(normalize(vPosVS-uSpotlights[i]), vVSSpotlightDirection);
        
        tmplight = tmplight * pow(max(0.0, cosangle), 5.0); //focus luce, più larga o più concentrata
        
        spotlightLight += tmplight;
      }
      vec3 spotlightColor = vec3(0.996, 0.698, 0.902) * spotlightLight;

      //Sommo tutte le componenti per il colore finale
      gl_FragColor = vec4(diffuseColor + specularColor + spotlightColor + 
      (headlightColorDx.rgb * headlightColorDx.a) + 
      (headlightColorSx.rgb * headlightColorSx.a), 1.0);

    }
  `;

  //Creo il vertex shader
  var vertexShader = gl.createShader(gl.VERTEX_SHADER);
  gl.shaderSource(vertexShader, vertexShaderSource);
  gl.compileShader(vertexShader);

  //Creo il fragment shader
  var fragmentShader = gl.createShader(gl.FRAGMENT_SHADER);
  gl.shaderSource(fragmentShader, fragmentShaderSource);
  gl.compileShader(fragmentShader);

  //Creo il shader program
  var aPositionIndex = 0;
  var aNormalIndex = 1;
  var aTextureCoordsIndex = 2; //indice texture: dove andare a mettere le coordinate della texture
  var shaderProgram = gl.createProgram();
  gl.attachShader(shaderProgram, vertexShader);
  gl.attachShader(shaderProgram, fragmentShader);
  gl.bindAttribLocation(shaderProgram, aPositionIndex, "aPosition");
  gl.bindAttribLocation(shaderProgram, aNormalIndex, "aNormal");
  gl.bindAttribLocation(shaderProgram, aTextureCoordsIndex, "aTextureCoords");
  gl.linkProgram(shaderProgram);

  // If creating the shader program failed, alert
  if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
    var str = "Unable to initialize the shader program.\n\n";
    str += "VS:\n" + gl.getShaderInfoLog(vertexShader) + "\n\n";
    str += "FS:\n" + gl.getShaderInfoLog(fragmentShader) + "\n\n";
    str += "PROG:\n" + gl.getProgramInfoLog(shaderProgram);
    alert(str);
  }

  shaderProgram.aPositionIndex = aPositionIndex;
  shaderProgram.aNormalIndex = aNormalIndex;
  shaderProgram.aTextureCoordsIndex = aTextureCoordsIndex;
  shaderProgram.uModelViewMatrixLocation = gl.getUniformLocation(shaderProgram, "uModelViewMatrix");
  shaderProgram.uProjectionMatrixLocation = gl.getUniformLocation(shaderProgram, "uProjectionMatrix");
  shaderProgram.uColorLocation = gl.getUniformLocation(shaderProgram, "uColor");
  shaderProgram.uViewSpaceLightDirectionLocation = gl.getUniformLocation(shaderProgram, "uViewSpaceLightDirection");
  shaderProgram.uViewMatrixLocation = gl.getUniformLocation(shaderProgram, "uViewMatrix");
  shaderProgram.uInverseViewMatrixLocation = gl.getUniformLocation(shaderProgram, "uInverseViewMatrix"); //inversa view matrix

  //spotlights
  shaderProgram.uSpotlightsLocation = gl.getUniformLocation(shaderProgram, "uSpotlights");
  //textures
  shaderProgram.uTexturesEnabledLocation = gl.getUniformLocation(shaderProgram, "uTexturesEnabled");

  shaderProgram.uSamplerLocation = gl.getUniformLocation(shaderProgram, "uSampler");
  shaderProgram.uHeadlightSamplerLocation = gl.getUniformLocation(shaderProgram, "uHeadlightSampler"); //headlights texture

  //headlights
  shaderProgram.uHeadlightSxMatrixLocation = gl.getUniformLocation(shaderProgram, "uHeadlightSxMatrix");
  shaderProgram.uHeadlightDxMatrixLocation = gl.getUniformLocation(shaderProgram, "uHeadlightDxMatrix");

  //shadow maps
  shaderProgram.uHeadlightSxLocation = gl.getUniformLocation(shaderProgram, "uHeadlightSx");
  shaderProgram.uHeadlightDxLocation = gl.getUniformLocation(shaderProgram, "uHeadlightDx");

  return shaderProgram;
};

