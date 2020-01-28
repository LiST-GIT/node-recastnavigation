var lodash = require( 'lodash' );
var recastnavigation = require( '../index.js' );

// var tileMesh = new recastnavigation.SampleTileMesh();
// var fname = __dirname + '/map.bytes';
// console.log( tileMesh.load( fname ) );
// tileMesh.build();
// var start = null;
// var end = null;
// console.log( start = tileMesh.findNearestPoly( 7072 / 100, 0, 3618 / 100, 0, 1000, 0 ) );
// console.log( end = tileMesh.findNearestPoly( 7075 / 100, 0, 3618 / 100, 0, 1000, 0 ) );
// console.log( tileMesh.findPath( start.x, start.y, start.z, end.x, end.y, end.z, 1000 ) );
// return;

console.log( 'SAMPLE_POLYAREA_GROUND: ' + recastnavigation.SAMPLE_POLYAREA_GROUND );
console.log( 'SAMPLE_POLYAREA_WATER: ' + recastnavigation.SAMPLE_POLYAREA_WATER );
console.log( 'SAMPLE_POLYAREA_ROAD: ' + recastnavigation.SAMPLE_POLYAREA_ROAD );
console.log( 'SAMPLE_POLYAREA_DOOR: ' + recastnavigation.SAMPLE_POLYAREA_DOOR );
console.log( 'SAMPLE_POLYAREA_GRASS: ' + recastnavigation.SAMPLE_POLYAREA_GRASS );
console.log( 'SAMPLE_POLYAREA_JUMP: ' + recastnavigation.SAMPLE_POLYAREA_JUMP );

console.log( 'SAMPLE_POLYFLAGS_WALK: ' + recastnavigation.SAMPLE_POLYFLAGS_WALK );
console.log( 'SAMPLE_POLYFLAGS_SWIM: ' + recastnavigation.SAMPLE_POLYFLAGS_SWIM );
console.log( 'SAMPLE_POLYFLAGS_DOOR: ' + recastnavigation.SAMPLE_POLYFLAGS_DOOR );
console.log( 'SAMPLE_POLYFLAGS_JUMP: ' + recastnavigation.SAMPLE_POLYFLAGS_JUMP );
console.log( 'SAMPLE_POLYFLAGS_DISABLED: ' + recastnavigation.SAMPLE_POLYFLAGS_DISABLED );
console.log( 'SAMPLE_POLYFLAGS_ALL: ' + recastnavigation.SAMPLE_POLYFLAGS_ALL );

console.log( 'DT_STRAIGHTPATH_START: ' + recastnavigation.DT_STRAIGHTPATH_START );
console.log( 'DT_STRAIGHTPATH_END: ' + recastnavigation.DT_STRAIGHTPATH_END );
console.log( 'DT_STRAIGHTPATH_OFFMESH_CONNECTION: ' + recastnavigation.DT_STRAIGHTPATH_OFFMESH_CONNECTION );

var soloMesh = new recastnavigation.SampleSoloMesh();

console.time( 'solo mesh load' );
console.log( soloMesh.load( __dirname + '/nav_test.obj' ) );
console.timeEnd( 'solo mesh load' );


soloMesh.addOffMeshConnection(
	31.148533, -1.923576, -22.547119,
	16.911285, -2.370018, -20.976799,
	2.0, 1, recastnavigation.SAMPLE_POLYAREA_JUMP, recastnavigation.SAMPLE_POLYFLAGS_JUMP );

console.log( 'solo mesh offmeshlink count: ' + soloMesh.getOffMeshConnectionCount() );

console.time( 'solo mesh build' );
soloMesh.build();
console.timeEnd( 'solo mesh build' );


console.time( 'point a' );
var a = soloMesh.findNearestPoly( 0, 0, 0, 0, 0, 0 );
console.timeEnd( 'point a' );
console.log( 'a: ', a );

console.time( 'point b' );
var b = soloMesh.findNearestPoly( 45, 0, -29, 0, 500, 0 );
console.timeEnd( 'point b' );
console.log( 'b: ', b );

console.time( 'point c' );
var c = soloMesh.findNearestPoly( 19, 0, 9, 0, 500, 0 );
console.timeEnd( 'point c' );
console.log( 'c: ', c );

console.log( 'find path:' );
console.time( 'solo mesh find path' );
console.log( soloMesh.findPath(
	45.593132, -1.753937, -29.563519,
	19.778542, -2.368042, 9.467735,
	1000 ).map( vector3 => JSON.stringify( vector3 ) ).join( '\n' ) );
console.timeEnd( 'solo mesh find path' );
