function image2grid


a = imread('lambo.jpg');
g = im2bw(a,0.9);
g = [ones(571,300),g,ones(571,300)];
g(end-180:end,:) = 0;
imshow(g)
size(g)
% a = imread('kaeferMod.jpg');
% B = im2bw(a,0.9);
% % remove parts
% B(1:20,:) = 1;
% B(end-5:end,:) = 1;
% B =[ones(413,400),B,ones(413,400)];
% B(end-15:end,:) = 0; % ground
% % remove some noise
% B(200:250,450:550) = 1;
% B(280:290,945:955) = 1;
% g= B;

% we need to store information about dimension
[NyPlus1,NxPlus1] = size(g);
Ny = NyPlus1 -1 ;
Nx = NxPlus1 -1 ;

% Dimension is not important for input, because we store Ny and Nx

LinearOutput = [];
for i=1:Ny+1
    for j=1:Nx+1
        LinearOutput = [LinearOutput, g(i,j)]; % this is not fast, but anyhow...
    end
end

LinearOutput = [Ny,Nx, LinearOutput];
dlmwrite('lambo2.txt',LinearOutput,'delimiter',' ');

end