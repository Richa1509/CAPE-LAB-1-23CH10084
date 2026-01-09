R = 0.08206;      
T = 523;          
P = 10;           
Tc = 407.5;       
Pc = 111.3;       

% Redlich-Kwong constants
a = 0.42748 * R^2 * Tc^2.5 / Pc;
b = 0.08664 * R * Tc / Pc;

% Residual function
f = @(v) (R*T)./(v - b) - a./(sqrt(T).*v.*(v + b)) - P;

% Initial guess
v0 = R*T/P;

% Start timer
tic
v = fzero(f, v0);
time_rk = toc;

disp(v)
disp(time_rk)



