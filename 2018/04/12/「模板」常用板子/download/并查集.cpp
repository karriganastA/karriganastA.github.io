int gf(int x){return fa[x]==x?x:fa[x]=gf(fa[x]);}
