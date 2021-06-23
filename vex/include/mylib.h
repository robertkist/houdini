// include guards: those two lines and #endif at the end of this file will prevent multiple including of this header
#ifndef _myLib_
#define _myLib_

/* ******************************************* */
/* **** FUNCTIONS FOR WORKING WITH CURVES **** */
/* ******************************************* */

// Returns true(1) if the middle point (b) is a peak - i.e. if it is
// higher on the X axis than the other two points.
int curve_peak_x(vector2 a; vector2 b; vector2 c) {
    return a.x < b.y && c.x < b.x;
}

// Returns true(1) if the middle point (b) is a peak - i.e. if it is
// higher on the Y axis than the other two points.
int curve_peak_y(vector2 a; vector2 b; vector2 c) {
    return a.y < b.y && c.y < b.y;
}

// Returns true(1) if the middle point (b) is a peak - i.e. if it is
// higher on the Z axis than the other two points.
int curve_peak_z(vector2 a; vector2 b; vector2 c) {
    return a.z < b.z && c.z < b.z;
}

// Calculates and returns normal vector for a given point on a curve.
// Inputs are the point number (@ptnum) and the point (@P).
// The return value can be assigned to @N.
vector curve_point_normal(int ptnum; vector P) {
    vector N = {0, 0, 0};
    int nbs[] = neighbours(0, ptnum);
    if (len(nbs) > 1) {     // curve point that is not the first or last
        vector a = pointattrib(0, "P", nbs[0], 1);
        vector c = pointattrib(0, "P", nbs[1], 1);
        vector ba = normalize(a - P);
        vector bc = normalize(c - P);
        vector ac_half = (bc - ba) * 0.5;
        N = P - (a + ac_half);
    } else {
        vector b = pointattrib(0, "P", nbs[0], 1);
        vector ab = P - b;
        N.x = ab.x;
        if (ptnum == 0) {   // first curve point
            N.y = -ab.z;
            N.z = ab.y;
        } else {            // last curve point
            N.y = ab.z;
            N.z = -ab.y;    
        }
    }
    return normalize(N);
}

// Calculates and returns the angle (in radians) of the edges of a point on a curve.
// Inputs are the point number (@ptnum) and the point (@P).
// Returns 0.0 for the first and last point on the curve.
// The angle is always measured for the opposite of where the normal is pointing to.
float curve_point_angle(int ptnum; vector P) {
    int nbs[] = neighbours(0, ptnum);
    if (len(nbs) > 1) {
        vector a = pointattrib(0, "P", nbs[0], 1);
        vector c = pointattrib(0, "P", nbs[1], 1);
        vector ba = normalize(a - P);
        vector bc = normalize(c - P);
        return acos(dot(ba, bc));
    } 
    return 0.0;   
}

/* ********************************************** */
/* **** FUNCTIONS FOR WORKING WITH TRIANGLES **** */
/* ********************************************** */

// Calculates the radius of a triangle's circumcenter.
// Inputs are the 3 points of the triangle (a,b,c).
float circumcenter_radius(vector a; vector b; vector c) {
    float aa = length(a - b);
    float bb = length(c - b);
    float cc = length(a - c);
    float dividend = aa * bb * cc; 
    float divisor = sqrt((aa+bb+cc) * (bb+cc-aa) * (cc+aa-bb) * (aa+bb-cc));
    return dividend / divisor;
}

// Calculates the position of a triangle's circumcenter (aka O).
// Inputs are the 3 points of the triangle (a,b,c).
// Since O is equally distant from all 3 corners, the radius can be calculated like this:
//    float radius = length(c - circumcenter_origin(a, b, c));
vector circumcenter_origin(vector a; vector b; vector c) {
    vector ac = c - a;
    vector ab = b - a;
    vector tocc = ((length2(ac) * cross(cross(ab, ac), ab)) + 
                   (length2(ab) * cross(cross(ac, ab), ac)))
                   / (2 * length2(cross(ab, ac)));
    float radius = length(tocc);
    return a + tocc;
}

/* ************************ */
/* **** MISC FUNCTIONS **** */
/* ************************ */

void texture_to_vertex_color() {

}

// end of include guards
#endif 
