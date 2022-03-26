///// Definizione cilindro
/////
///// La "risoluzione" è il numero di faccie usato per fare il cilindro
///// Esso è centrato all'origine, giacente nel piano XZ
///// Ha altezza 2.0 di raggio 1.0

function Cylinder (resolution) {

  this.name = "cylinder";

	//Definizione vertici
	this.vertices = new Float32Array(3*(2*resolution+2));
	
	var radius = 1.0;
	var angle;
	var step = 6.283185307179586476925286766559 / resolution;
	
	//cerchio inferiore
	var vertexoffset = 0;
	for(var i = 0; i < resolution; i++){
		angle = step * i;
		
		this.vertices[vertexoffset] = radius * Math.cos(angle);
		this.vertices[vertexoffset+1] = 0.0;
		this.vertices[vertexoffset+2] = radius * Math.sin(angle);
		vertexoffset += 3;
	}
	
	//cerchio superiore
	for(var i = 0; i < resolution; i++){
		angle = step * i;
		
		this.vertices[vertexoffset] = radius * Math.cos(angle);
		this.vertices[vertexoffset+1] = 2.0;
		this.vertices[vertexoffset+2] = radius * Math.sin(angle);
		vertexoffset += 3;
	}
	
	this.vertices[vertexoffset] = 0.0;
	this.vertices[vertexoffset+1] = 0.0;
	this.vertices[vertexoffset+2] = 0.0;
	vertexoffset += 3;
	
	this.vertices[vertexoffset] = 0.0;
	this.vertices[vertexoffset+1] = 2.0;
	this.vertices[vertexoffset+2] = 0.0;
	
	
	//definizione triangoli
	this.triangleIndices = new Uint16Array(3*4*resolution);
	
	//superficie laterale
	var triangleoffset = 0;
	for(var i = 0; i < resolution; i++){
		this.triangleIndices[triangleoffset] = i;
		this.triangleIndices[triangleoffset+1] = (i+1) % resolution;
		this.triangleIndices[triangleoffset+2] = (i % resolution) + resolution;
		triangleoffset += 3;
		
		this.triangleIndices[triangleoffset] = (i % resolution) + resolution;
		this.triangleIndices[triangleoffset+1] = (i+1) % resolution;
		this.triangleIndices[triangleoffset+2] = ((i+1) % resolution) + resolution;
		triangleoffset += 3;
	}
	
	//Parte bassa del cilindro
	for (var i = 0; i < resolution; i++){
		this.triangleIndices[triangleoffset] = i;
		this.triangleIndices[triangleoffset+1] = (i+1) % resolution;
		this.triangleIndices[triangleoffset+2] = 2*resolution;
		triangleoffset += 3;
	}
	
	//Parte alta
	for (var i = 0; i < resolution; i++){
		this.triangleIndices[triangleoffset] = resolution + i;
		this.triangleIndices[triangleoffset+1] = ((i+1) % resolution) + resolution;
		this.triangleIndices[triangleoffset+2] = 2*resolution+1;
		triangleoffset += 3;
	}
		
	this.numVertices = this.vertices.length/3;
	this.numTriangles = this.triangleIndices.length/3;
}
