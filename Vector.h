#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
#include "globals.h"
#include <string>
#include <stdio.h>
#include <assert.h>
using namespace std;
#define EPSILON .000001
class Vector{
	NT vals[3];
	public:

		Vector () {
			vals[0] = vals[1] = vals[2] = 0;
		}
		Vector (NT x, NT y, NT z) {
			vals[0] = x;
			vals[1] = y;
			vals[2] = z;

		}
		Vector (NT *vals_) {
			for (int i=0; i<3; i++) {
				vals[i] = vals_[i];
			}
		}
		Vector VTo(const Vector &v) {
			return Vector(v[0] - vals[0], v[1] - vals[1], v[2] - vals[2]);
		}
		NT &operator[]( int n ){
			return vals[n]; 
		}
		NT operator[]( const int n )const{
			return vals[n];
		}
		Vector operator-()const{
			return Vector( vals[0], vals[1], vals[2]); 
		}
		Vector operator*( NT scale )const{
			return Vector( vals[0]*scale,vals[1]*scale,vals[2]*scale );
		}
		Vector operator*( const Vector &q )const{
			return Vector( vals[0]*q[0],vals[1]*q[1],vals[2]*q[2]);
		}
		Vector operator/( NT scale )const{
			return Vector( vals[0]/scale,vals[1]/scale,vals[2]/scale );
		}
		Vector operator/( const Vector &q )const{
			return Vector( vals[0]/q[0],vals[1]/q[1],vals[2]/q[2] );
		}
		Vector operator+( const Vector &q )const{
			return Vector( vals[0]+q[0],vals[1]+q[1],vals[2]+q[2] );
		}
		Vector operator-( const Vector &q )const{
			return Vector( vals[0]-q[0],vals[1]-q[1],vals[2]-q[2] );
		}
		Vector &operator*=( NT scale ){
			vals[0]*=scale;vals[1]*=scale;vals[2]*=scale;return *this;
		}
		Vector &operator*=( const Vector &q ){
			vals[0]*=q[0];vals[1]*=q[1];vals[2]*=q[2];return *this;
		}
		Vector &operator/=( NT scale ){
			vals[0]/=scale;vals[1]/=scale;vals[2]/=scale;return *this;
		}
		Vector &operator/=( const Vector &q ){
			vals[0]/=q[0];vals[1]/=q[1];vals[2]/=q[2];return *this;
		}
		Vector &operator+=( const Vector &q ){
			vals[0]+=q[0];vals[1]+=q[1];vals[2]+=q[2];return *this;
		}
		Vector &operator-=( const Vector &q ){
			vals[0]-=q[0];vals[1]-=q[1];vals[2]-=q[2];return *this;
		}
		bool operator<( const Vector &q )const{
			if( fabs(vals[0]-q[0])>EPSILON ) return vals[0]<q[0] ? true : false;
			if( fabs(vals[1]-q[1])>EPSILON ) return vals[1]<q[1] ? true : false;
			return fabs(vals[2]-q[2])>EPSILON && vals[2]<q[2];
		}
		bool operator==( const Vector &q )const{
			return fabs(vals[0]-q[0])<=EPSILON && fabs(vals[1]-q[1])<=EPSILON && fabs(vals[2]-q[2])<=EPSILON;
		}
		bool operator!=( const Vector &q )const{
			return fabs(vals[0]-q[0])>EPSILON || fabs(vals[1]-q[1])>EPSILON || fabs(vals[2]-q[2])>EPSILON;
		}
		NT dot( const Vector &q )const{
			return vals[0]*q[0]+vals[1]*q[1]+vals[2]*q[2];
		}
		Vector cross( const Vector &q )const{
			return Vector( vals[1]*q[2]-vals[2]*q[1],vals[2]*q[0]-vals[0]*q[2],vals[0]*q[1]-vals[1]*q[0] );
		}
		NT len()const{
			return sqrt(vals[0]*vals[0]+vals[1]*vals[1]+vals[2]*vals[2]);
		}
		NT lenSqr()const{
			return vals[0]*vals[0]+vals[1]*vals[1]+vals[2]*vals[2];
		}
		NT dist( const Vector &q )const{
			NT dx=vals[0]-q[0],dy=vals[1]-q[1],dz=vals[2]-q[2];return sqrt(dx*dx+dy*dy+dz*dz);
		}
		NT distSqr( const Vector &q) {
			NT dx=vals[0]-q[0],dy=vals[1]-q[1],dz=vals[2]-q[2];return dx*dx+dy*dy+dz*dz;
		}
		Vector normalized()const{
			NT l=len();return Vector( vals[0]/l,vals[1]/l,vals[2]/l );
		}
		void normalize(){
			NT l=len();vals[0]/=l;vals[1]/=l;vals[2]/=l;
		}
		NT yaw()const{
			return -atan2f( vals[0],vals[2] );
		}
		NT pitch()const{
			return -atan2f( vals[1],sqrtf( vals[0]*vals[0]+vals[2]*vals[2] ) );
		}
		void clear(){
			vals[0] = vals[1] = vals[2] = 0;
		}
		void rotateccw() {
			const NT dx = vals[0];
			const NT dy = vals[1];
			vals[0] = -dy;
			vals[1] = dx;
		}
		void rotatecw() {
			const NT dx = vals[0];
			const NT dy = vals[1];
			vals[0] = dy;
			vals[1] = -dx;
		}
		string asStr() {
			char buffer[100];
			int n = sprintf(buffer, "x: %f, y: %f, z: %f", vals[0], vals[1], vals[2]);
			assert(n >= 0);	
			return string(buffer);
		}
};
#endif
