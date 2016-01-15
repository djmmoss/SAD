function Fk = ewrndft(ft,t,n,d)    
%Sample streaming wrapper for the ewrdft
    N = size(ft,1);
    Fk = zeros(N+1,n);
    x_prev = 0;
    for i = 1:N
        [~, tmp] = ewrdft_update(Fk(i,:)', ft(i), t(i) - x_prev, d);
        Fk(i+1,:) = tmp';
        x_prev = t(i);
    end
end