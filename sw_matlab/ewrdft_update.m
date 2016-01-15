function [Pk_updated, Fk_updated] = ewrdft_update(Fk_old, f, delta_t, d)
% ewrdft_update  Recursively updated DFT 
%   Inputs:
%   Fk_old:     Previous DFT vector
%   f:          New sample value
%   delta_t:    Time lapsed after the last update
%   d:          Exponential Weight
%
%   Outputs:
%   Pk_updated: Updated power vector
%   Fk_updated: Updated DFT vector

    n = size(Fk_old,1);
    ejwdx = exp( 2j * pi * (0:n-1)'/n * delta_t);
    Fk_updated = Fk_old.*ejwdx.*d + f*(1-d);
    Pk_updated = abs(Fk_updated);
end

