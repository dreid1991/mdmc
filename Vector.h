#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
#include "globals.h"
#include <string>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <iostream>
using namespace std;
#define EPSILON .000001

template <typename T, typename K>
class VectorGeneric;

typedef VectorGeneric<float, int> Vector;
typedef VectorGeneric<int, float> VectorInt;

//theme for these operations is that if we're operating on unlike types, switch to float representation.  would like better way to do this
template <typename T, typename K>
class VectorGeneric {
	T vals[3];
	public:

		VectorGeneric<T, K> () {
			vals[0] = vals[1] = vals[2] = 0;
		}
		VectorGeneric<T, K> (float x, float y, float z) {  // if using literals, have to cast each as int or float so compiler can distinguish between these two constructors
			vals[0] = x;
			vals[1] = y;
			vals[2] = z;
		}
		VectorGeneric<T, K> (int x, int y, int z) {
			vals[0] = x;
			vals[1] = y;
			vals[2] = z;
		}
		VectorGeneric<T, K> (int vals_[3]) {
			for (int i=0; i<3; i++) {
				vals[i] = (T) vals_[i];
			}
		}
		VectorGeneric<T, K> (float vals_[3]) {
			for (int i=0; i<3; i++) {
				vals[i] = (T) vals_[i];
			}
		}
		void zero() {
			vals[0] = vals[1] = vals[2] = 0;
		}
		VectorGeneric<T, K> VTo(const VectorGeneric<T, K> &v) {
			return VectorGeneric<T, K>(v[0] - vals[0], v[1] - vals[1], v[2] - vals[2]);
		}
		VectorGeneric<float, int> VTo(const VectorGeneric<K, T> &v) {
			return VectorGeneric<float, int>(v[0] - vals[0], v[1] - vals[1], v[2] - vals[2]);
		}
		T sum() {
			return vals[0] + vals[1] + vals[2];
		}
		T &operator[]( int n ){
			return vals[n]; 
		}
		T operator[]( const int n )const{
			return vals[n];
		}

		VectorGeneric<T, K> abs() {
			return VectorGeneric<T, K>((T) fabs(vals[0]), (T) fabs(vals[1]), (T) fabs(vals[2]));
		}
		VectorGeneric<T, K> operator-()const{
			return VectorGeneric<T, K>(-vals[0], -vals[1], -vals[2]); 
		}
		VectorGeneric<float, int> operator*( float scale )const{
			return VectorGeneric<float, int>( vals[0]*scale,vals[1]*scale,vals[2]*scale );
		}

		VectorGeneric<T, K> operator*( const VectorGeneric<T, K> &q )const{
			return VectorGeneric<T, K>( vals[0]*q[0],vals[1]*q[1],vals[2]*q[2]);
		}
		VectorGeneric<float, int> operator*( const VectorGeneric<K, T> &q )const{
			return VectorGeneric<float, int>( vals[0]*q[0],vals[1]*q[1],vals[2]*q[2]);
		}

		VectorGeneric<T, K> operator/( int scale )const{
			return VectorGeneric<T, K>( vals[0]/scale,vals[1]/scale,vals[2]/scale );
		}
		VectorGeneric<float, int> operator/( float scale )const{
			return VectorGeneric<float, int>( vals[0]/scale,vals[1]/scale,vals[2]/scale );
		}

		VectorGeneric<T, K> operator/( const VectorGeneric<T, K> &q )const{
			return VectorGeneric<T, K>( vals[0]/q[0],vals[1]/q[1],vals[2]/q[2] );
		}
		VectorGeneric<float, int> operator/( const VectorGeneric<K, T> &q )const{
			return VectorGeneric<float, int>( vals[0]/q[0],vals[1]/q[1],vals[2]/q[2] );
		}

		VectorGeneric<T, K> operator+( const VectorGeneric<T, K> &q )const{
			return VectorGeneric<T, K>( vals[0]+q[0],vals[1]+q[1],vals[2]+q[2] );
		}
		VectorGeneric<float, int> operator+( const VectorGeneric<K, T> &q )const{
			return VectorGeneric<float, int>( vals[0]+q[0],vals[1]+q[1],vals[2]+q[2] );
		}

		VectorGeneric<T, K> operator-( const VectorGeneric<T, K> &q )const{
			return VectorGeneric<T, K>( vals[0]-q[0],vals[1]-q[1],vals[2]-q[2] );
		}
		VectorGeneric<float, int> operator-( const VectorGeneric<K, T> &q )const{
			return VectorGeneric<float, int>( vals[0]-q[0],vals[1]-q[1],vals[2]-q[2] );
		}

		VectorGeneric<T, K> &operator*=( int scale ){
			vals[0]*=scale;vals[1]*=scale;vals[2]*=scale;return *this; // *=, /=, etc won't promote types like binary operations
		}
		VectorGeneric<T, K> &operator*=( float scale ){
			vals[0]*=scale;vals[1]*=scale;vals[2]*=scale;return *this;
		}

		VectorGeneric<T, K> &operator*=( const VectorGeneric<T, K> &q ){
			vals[0]*=q[0];vals[1]*=q[1];vals[2]*=q[2];return *this;
		}
		VectorGeneric<T, K> &operator*=( const VectorGeneric<K, T> &q ){
			vals[0]*=q[0];vals[1]*=q[1];vals[2]*=q[2];return *this;
		}

		VectorGeneric<T, K> &operator/=( int scale ){
			vals[0]/=scale;vals[1]/=scale;vals[2]/=scale;return *this;
		}
		VectorGeneric<T, K> &operator/=( float scale ){
			vals[0]/=scale;vals[1]/=scale;vals[2]/=scale;return *this;
		}

		VectorGeneric<T, K> &operator/=( const VectorGeneric<T, K> &q ){
			vals[0]/=q[0];vals[1]/=q[1];vals[2]/=q[2];return *this;
		}
		VectorGeneric<T, K> &operator/=( const VectorGeneric<K, T> &q ){
			vals[0]/=q[0];vals[1]/=q[1];vals[2]/=q[2];return *this;
		}

		VectorGeneric<T, K> &operator+=( const VectorGeneric<T, K> &q ){
			vals[0]+=q[0];vals[1]+=q[1];vals[2]+=q[2];return *this;
		}
		VectorGeneric<T, K> &operator+=( const VectorGeneric<K, T> &q ){
			vals[0]+=q[0];vals[1]+=q[1];vals[2]+=q[2];return *this;
		}

		VectorGeneric<T, K> &operator-=( const VectorGeneric<T, K> &q ){
			vals[0]-=q[0];vals[1]-=q[1];vals[2]-=q[2];return *this;
		}
		VectorGeneric<T, K> &operator-=( const VectorGeneric<K, T> &q ){
			vals[0]-=q[0];vals[1]-=q[1];vals[2]-=q[2];return *this;
		}
		bool operator<( const VectorGeneric<T, K> &q )const{
			if( fabs(vals[0]-q[0])>EPSILON ) return vals[0]<q[0] ? true : false;
			if( fabs(vals[1]-q[1])>EPSILON ) return vals[1]<q[1] ? true : false;
			return fabs(vals[2]-q[2])>EPSILON && vals[2]<q[2];
		}
		bool operator<( const VectorGeneric<K, T> &q )const{
			if( fabs(vals[0]-q[0])>EPSILON ) return vals[0]<q[0] ? true : false;
			if( fabs(vals[1]-q[1])>EPSILON ) return vals[1]<q[1] ? true : false;
			return fabs(vals[2]-q[2])>EPSILON && vals[2]<q[2];
		}

		bool operator==( const VectorGeneric<T, K> &q )const{
			return fabs(vals[0]-q[0])<=EPSILON && fabs(vals[1]-q[1])<=EPSILON && fabs(vals[2]-q[2])<=EPSILON;
		}
		bool operator==( const VectorGeneric<K, T> &q )const{
			return fabs(vals[0]-q[0])<=EPSILON && fabs(vals[1]-q[1])<=EPSILON && fabs(vals[2]-q[2])<=EPSILON;
		}

		bool operator!=( const VectorGeneric<T, K> &q )const{
			return fabs(vals[0]-q[0])>EPSILON || fabs(vals[1]-q[1])>EPSILON || fabs(vals[2]-q[2])>EPSILON;
		}
		bool operator!=( const VectorGeneric<K, T> &q )const{
			return fabs(vals[0]-q[0])>EPSILON || fabs(vals[1]-q[1])>EPSILON || fabs(vals[2]-q[2])>EPSILON;
		}

		float dot( const VectorGeneric<T, K> &q )const{
			return vals[0]*q[0]+vals[1]*q[1]+vals[2]*q[2];
		}
		float dot( const VectorGeneric<K, T> &q )const{
			return vals[0]*q[0]+vals[1]*q[1]+vals[2]*q[2];
		}
		VectorGeneric<T, K> cross( const VectorGeneric<T, K> &q )const{
			return VectorGeneric<T, K>( vals[1]*q[2]-vals[2]*q[1],vals[2]*q[0]-vals[0]*q[2],vals[0]*q[1]-vals[1]*q[0] );
		}
		VectorGeneric<float, int> cross( const VectorGeneric<K, T> &q )const{
			return VectorGeneric<float, int>( vals[1]*q[2]-vals[2]*q[1],vals[2]*q[0]-vals[0]*q[2],vals[0]*q[1]-vals[1]*q[0] );
		}
		float len()const{
			return sqrt((float) vals[0]*vals[0]+vals[1]*vals[1]+vals[2]*vals[2]);
		}
		float lenSqr()const{
			return vals[0]*vals[0]+vals[1]*vals[1]+vals[2]*vals[2];
		}
		float dist( const VectorGeneric<T, K> &q )const{
			float dx=vals[0]-q[0],dy=vals[1]-q[1],dz=vals[2]-q[2];return sqrt(dx*dx+dy*dy+dz*dz);
		}
		float dist( const VectorGeneric<K, T> &q )const{
			float dx=vals[0]-q[0],dy=vals[1]-q[1],dz=vals[2]-q[2];return sqrt(dx*dx+dy*dy+dz*dz);
		}

		float distSqr( const VectorGeneric<T, K> &q) {
			float dx=vals[0]-q[0],dy=vals[1]-q[1],dz=vals[2]-q[2];return dx*dx+dy*dy+dz*dz;
		}
		float distSqr( const VectorGeneric<K, T> &q) {
			float dx=vals[0]-q[0],dy=vals[1]-q[1],dz=vals[2]-q[2];return dx*dx+dy*dy+dz*dz;
		}

		VectorGeneric<float, int> normalized()const{
			float l=len();return VectorGeneric<float, int>( vals[0]/l,vals[1]/l,vals[2]/l );
		}
		void normalize(){
			float l=len();vals[0]/=l;vals[1]/=l;vals[2]/=l; //will not necessarily normalize int vectors
		}
		float yaw()const{
			return -atan2f( vals[0],vals[2] );
		}
		float pitch()const{
			return -atan2f( vals[1],sqrtf( vals[0]*vals[0]+vals[2]*vals[2] ) );
		}
		void clear(){
			vals[0] = vals[1] = vals[2] = 0;
		}

		string asStr() {
			char buffer[100];
			float x = vals[0], y = vals[1], z = vals[2];
			int n = sprintf(buffer, "x: %f, y: %f, z: %f", x, y, z);
			assert(n >= 0);	
			return string(buffer);
		}
		VectorGeneric<T, K> &operator=(const VectorGeneric<K, T> &other) {
			for (int i=0; i<3; i++) {
				vals[i] = other[i];
			}
			return *this;
		}
		VectorGeneric<T, K> (const VectorGeneric<K, T> &other) {
			for (int i=0; i<3; i++) {
				vals[i] = other[i];
			}
		}
};

#endif
